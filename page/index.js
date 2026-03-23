import * as hmUI from "@zos/ui";
import * as display from "@zos/display";
import { getDeviceInfo } from "@zos/device";
import { onGesture, GESTURE_LEFT, GESTURE_RIGHT, GESTURE_DOWN, onKey, KEY_BACK, KEY_EVENT_UP } from "@zos/interaction";
import { push } from "@zos/router";
import { BasePage } from "@zeppos/zml/base-page";
import { log as Logger } from "@zos/utils";

const logger = Logger.getLogger("page");

const FONT = {
  TITLE: 28,
  HEADER: 24,
  BODY: 20
};

const LAYOUT = {
  X: 18,
  W: 354
};

const SAFE_TOP = 56;

const COLORS = {
  RED: 0xFF1801,
  WHITE: 0xFFFFFF,
  GRAY: 0x888888,
  YELLOW: 0xFFAA00
};

Page(BasePage({

  state: {
    f1Data: null,
    resultsData: null,
    DEVICE_WIDTH: 390,
    currentView: "main",
    testMode: false
  },

  onInit() {
    if (typeof display.setStayWake === "function") {
      display.setStayWake(true);
    }
    if (typeof display.resetBrightTime === "function") {
      display.resetBrightTime();
    }
    if (typeof display.setBrightTime === "function") {
      display.setBrightTime(600); // 10 minutes
    }

    const { width } = getDeviceInfo();
    this.state.DEVICE_WIDTH = width;

    // Polling every 5 seconds for live updates
    this.pollInterval = setInterval(() => {
      if (typeof display.setStayWake === "function") {
        display.setStayWake(true);
      }
      if (typeof display.resetBrightTime === "function") {
        display.resetBrightTime();
      }
      this.fetchData();
    }, 5000);

    onKey({
      callback: (keyCode, keyEvent) => {
        if (keyCode === KEY_BACK && keyEvent === KEY_EVENT_UP) {
          logger.log("BACK KEY PRESSED");
          if (this.state.currentView === "event_detail") {
            this.renderCalendar(this.state.calendarData);
            return true;
          }
          if (this.state.currentView !== "main") {
            this.state.currentView = "main";
            this.updateUI(this.state.f1Data);
            return true;
          }
          // On main screen, return true to prevent exit from back button
          // User must use other system methods to close if they really want to
          return true;
        }
        return false;
      }
    });

    onGesture({
      callback: (event) => {
        logger.log("GESTURE EVENT:", event);

        if (event === GESTURE_DOWN) {
          this.state.testMode = !this.state.testMode;
          hmUI.showToast({ text: this.state.testMode ? "SIM ON" : "SIM OFF" });
          this.fetchData();
          return true;
        }

        if (event === GESTURE_LEFT) {
          if (this.state.currentView === "main") {
            hmUI.showToast({ text: "Last Results" });
            this.loadResults();
            return true;
          } else if (this.state.currentView === "results") {
            hmUI.showToast({ text: "Next Race" });
            this.renderNextRace(this.state.f1Data?.upcoming);
            return true;
          } else if (this.state.currentView === "next") {
            hmUI.showToast({ text: "Driver Standings" });
            this.loadStandings();
            return true;
          } else if (this.state.currentView === "standings") {
            hmUI.showToast({ text: "Constructor Standings" });
            this.loadConstructorStandings();
            return true;
          } else if (this.state.currentView === "constructors") {
            hmUI.showToast({ text: "Calendar" });
            this.loadCalendar();
            return true;
          }
        }

        if (event === GESTURE_RIGHT) {
          if (this.state.currentView === "results") {
            this.state.currentView = "main";
            this.updateUI(this.state.f1Data);
            return true;
          } else if (this.state.currentView === "next") {
            this.loadResults();
            return true;
          } else if (this.state.currentView === "standings") {
            this.renderNextRace(this.state.f1Data?.upcoming);
            return true;
          } else if (this.state.currentView === "constructors") {
            this.loadStandings();
            return true;
          } else if (this.state.currentView === "calendar") {
            this.loadConstructorStandings();
            return true;
          } else if (this.state.currentView === "event_detail") {
            this.renderCalendar(this.state.calendarData);
            return true;
          }
        }

        return false;
      }
    });
  },

  onDestroy() {
    if (this.pollInterval) {
      clearInterval(this.pollInterval);
    }
    if (typeof display.setStayWake === "function") {
      display.setStayWake(false);
    }
  },

  build() {

    logger.log("BUILD");

    // =========================
    // 1. INIT UI FIRST (LOWER LAYER)
    // =========================
    this.updateUI(null);
    this.fetchData();
  },

  // =========================
  // DATA
  // =========================
  fetchData() {
    const method = this.state.testMode ? "GET_MOCK_DATA" : "GET_DATA";
    this.request({ method })
      .then((res) => {
        this.state.f1Data = res?.result;
        if (this.state.currentView === "main") {
          this.updateUI(this.state.f1Data);
        }
      })
      .catch((err) => {
        logger.log("fetchData failed", err);
        if (this.state.currentView === "main") {
          this.showError("Ensure the Zepp App is open on your phone and Bluetooth is on.");
        }
      });
  },

  loadResults() {
    logger.log("loadResults called");
    this.request({ method: "GET_RESULTS" })
      .then((res) => {
        const data = res?.result;
        if (data?.error === "NO_INTERNET") {
          this.showError("The phone has no internet connection.");
          return;
        }

        if (data && data.results) {
          this.state.resultsData = data;
          this.state.currentView = "results";
          this.renderResults(data);
        } else {
          this.renderResults({ raceName: "No Data", results: [] });
        }
      })
      .catch(() => {
        this.showError("Bluetooth connection lost with phone.");
      });
  },

  loadStandings() {
    logger.log("loadStandings called");
    this.request({ method: "GET_STANDINGS" })
      .then((res) => {
        const data = res?.result;
        if (data?.error === "NO_INTERNET") {
          this.showError("The phone has no internet connection.");
          return;
        }

        if (data && data.standings) {
          this.state.currentView = "standings";
          this.renderStandings(data);
        } else {
          this.renderStandings({ standings: [] });
        }
      })
      .catch(() => {
        this.showError("Bluetooth connection lost with phone.");
      });
  },

  loadConstructorStandings() {
    logger.log("loadConstructorStandings called");
    this.request({ method: "GET_CONSTRUCTOR_STANDINGS" })
      .then((res) => {
        const data = res?.result;
        if (data?.error === "NO_INTERNET") {
          this.showError("The phone has no internet connection.");
          return;
        }

        if (data && data.standings) {
          this.state.currentView = "constructors";
          this.renderConstructorStandings(data);
        } else {
          this.renderConstructorStandings({ standings: [] });
        }
      })
      .catch(() => {
        this.showError("Bluetooth connection lost with phone.");
      });
  },

  loadCalendar() {
    logger.log("loadCalendar called");
    this.request({ method: "GET_CALENDAR" })
      .then((res) => {
        const data = res?.result;
        if (data?.error === "NO_INTERNET") {
          this.showError("The phone has no internet connection.");
          return;
        }

        if (data && data.calendar) {
          this.state.calendarData = data;
          this.state.currentView = "calendar";
          this.renderCalendar(data);
        } else {
          this.renderCalendar({ calendar: [] });
        }
      })
      .catch(() => {
        this.showError("Bluetooth connection lost with phone.");
      });
  },

  // =========================
  // NEXT RACE UI
  // =========================
  renderNextRace(data) {
    logger.log("renderNextRace called");

    if (typeof display.setStayWake === "function") {
      display.setStayWake(true);
    }

    if (this.rootGroup) {
      hmUI.deleteWidget(this.rootGroup);
      this.rootGroup = null;
    }

    this.state.currentView = "next";

    this.rootGroup = hmUI.createWidget(hmUI.widget.GROUP, {
      x: 0,
      y: 0,
      w: 390,
      h: 450
    });

    this.rootGroup.createWidget(hmUI.widget.TEXT, {
      x: LAYOUT.X,
      y: SAFE_TOP,
      w: LAYOUT.W,
      h: 40,
      text: "NEXT RACE",
      color: COLORS.RED,
      text_size: FONT.HEADER,
      align_h: hmUI.align.CENTER_H
    });

    if (!data) {
      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: 0,
        y: 200,
        w: 390,
        h: 40,
        text: "NO DATA",
        color: COLORS.WHITE,
        text_size: FONT.BODY,
        align_h: hmUI.align.CENTER_H
      });
      return;
    }

    this.rootGroup.createWidget(hmUI.widget.TEXT, {
      x: LAYOUT.X,
      y: 100,
      w: LAYOUT.W,
      h: 60,
      text: `${data.flag || ""} ${data.name}\n${data.circuit || ""}`,
      color: COLORS.WHITE,
      text_size: 20,
      align_h: hmUI.align.CENTER_H
    });

    const sessions = data.sessions || [];
    let y = 170;

    sessions.forEach(s => {
      const utcDate = new Date(s.time.replace("Z", ""));
      const localTime = `${utcDate.getHours().toString().padStart(2, "0")}:${utcDate.getMinutes().toString().padStart(2, "0")}`;
      const localDate = `${(utcDate.getMonth() + 1)}/${utcDate.getDate()}`;

      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: 40,
        y,
        w: 120,
        h: 26,
        text: s.name,
        color: COLORS.YELLOW,
        text_size: 18
      });

      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: 160,
        y,
        w: 190,
        h: 26,
        text: `${localDate}  ${localTime}`,
        color: COLORS.WHITE,
        text_size: 18,
        align_h: hmUI.align.RIGHT
      });

      y += 32;
    });
  },

  // =========================
  // RESULTS UI
  // =========================
  renderResults(data) {
    logger.log("renderResults called with data:", JSON.stringify(data).substring(0, 200));

    if (typeof display.setStayWake === "function") {
      display.setStayWake(true);
    }

    if (this.rootGroup) {
      logger.log("Deleting old rootGroup");
      hmUI.deleteWidget(this.rootGroup);
      this.rootGroup = null;
    }

    const results = data?.results || [];
    logger.log("Results count:", results.length);

    this.rootGroup = hmUI.createWidget(hmUI.widget.GROUP, {
      x: 0,
      y: 0,
      w: 390,
      h: 450
    });

    this.rootGroup.createWidget(hmUI.widget.TEXT, {
      x: LAYOUT.X,
      y: SAFE_TOP,
      w: LAYOUT.W,
      h: 40,
      text: data?.raceName || "RESULTS",
      color: COLORS.RED,
      text_size: FONT.HEADER,
      align_h: hmUI.align.CENTER_H
    });

    if (!results.length) {
      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: 0,
        y: 200,
        w: 390,
        h: 40,
        text: "NO RESULTS",
        color: COLORS.WHITE,
        text_size: FONT.BODY,
        align_h: hmUI.align.CENTER_H
      });
      return;
    }

    logger.log("Creating SCROLL_LIST with data_array");

    const data_array = results.map(item => {
      let pts_text = `${item.points}`;
      if (item.points !== "DNF" && item.points !== "DNS") {
        pts_text += " pts";
      }

      return {
        pos: `P${item.position}`,
        name: `${item.flag} ${item.firstName} ${item.lastName}`,
        pts: pts_text
      };
    });

    this.rootGroup.createWidget(hmUI.widget.SCROLL_LIST, {
      x: 0,
      y: 110,
      w: 390,
      h: 340,
      item_space: 6,
      item_config: [
        {
          type_id: 1,
          item_height: 46,
          item_bg_color: 0x000000,
          item_bg_radius: 0,
          text_view: [
            { x: 18, y: 8, w: 50, h: 30, key: 'pos', color: COLORS.WHITE, text_size: 18 },
            { x: 70, y: 6, w: 180, h: 30, key: 'name', color: COLORS.WHITE, text_size: 20, align_h: hmUI.align.LEFT },
            { x: 260, y: 10, w: 110, h: 30, key: 'pts', color: COLORS.YELLOW, text_size: 18, align_h: hmUI.align.RIGHT }
          ],
          text_view_count: 3
        }
      ],
      item_config_count: 1,
      data_array: data_array,
      data_count: data_array.length,
      data_type_config: [
        {
          start: 0,
          end: Math.max(0, data_array.length - 1),
          type_id: 1
        }
      ],
      data_type_config_count: 1
    });
  },

  // =========================
  // CONSTRUCTOR STANDINGS UI
  // =========================
  renderConstructorStandings(data) {
    logger.log("renderConstructorStandings called");

    if (typeof display.setStayWake === "function") {
      display.setStayWake(true);
    }

    if (this.rootGroup) {
      hmUI.deleteWidget(this.rootGroup);
      this.rootGroup = null;
    }

    this.rootGroup = hmUI.createWidget(hmUI.widget.GROUP, {
      x: 0,
      y: 0,
      w: 390,
      h: 450
    });

    this.rootGroup.createWidget(hmUI.widget.TEXT, {
      x: LAYOUT.X,
      y: SAFE_TOP,
      w: LAYOUT.W,
      h: 40,
      text: "CONSTRUCTORS",
      color: COLORS.RED,
      text_size: FONT.HEADER,
      align_h: hmUI.align.CENTER_H
    });

    const standings = data?.standings || [];

    if (!standings.length) {
      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: 0,
        y: 200,
        w: 390,
        h: 40,
        text: data?.error ? "ERROR LOADING" : "NO STANDINGS",
        color: COLORS.WHITE,
        text_size: FONT.BODY,
        align_h: hmUI.align.CENTER_H
      });
      return;
    }

    const data_array = standings.map(item => ({
      pos: `${item.pos}`,
      name: `${item.flag} ${item.name}`,
      pts: `${item.points} pts`,
      color: item.color || COLORS.WHITE
    }));

    this.rootGroup.createWidget(hmUI.widget.SCROLL_LIST, {
      x: 0,
      y: 110,
      w: 390,
      h: 340,
      item_space: 6,
      item_config: [
        {
          type_id: 1,
          item_height: 46,
          item_bg_color: 0x000000,
          item_bg_radius: 0,
          text_view: [
            { x: 18, y: 8, w: 40, h: 30, key: 'pos', color: COLORS.WHITE, text_size: 18 },
            { x: 65, y: 6, w: 200, h: 30, key: 'name', color: COLORS.WHITE, color_key: 'color', text_size: 20, align_h: hmUI.align.LEFT },
            { x: 270, y: 10, w: 100, h: 30, key: 'pts', color: COLORS.YELLOW, text_size: 18, align_h: hmUI.align.RIGHT }
          ],
          text_view_count: 3
        }
      ],
      item_config_count: 1,
      data_array: data_array,
      data_count: data_array.length,
      data_type_config: [
        {
          start: 0,
          end: Math.max(0, data_array.length - 1),
          type_id: 1
        }
      ],
      data_type_config_count: 1
    });
  },

  // =========================
  // CALENDAR UI
  // =========================
  renderCalendar(data) {
    logger.log("renderCalendar called");

    if (typeof display.setStayWake === "function") {
      display.setStayWake(true);
    }

    if (this.rootGroup) {
      hmUI.deleteWidget(this.rootGroup);
      this.rootGroup = null;
    }

    this.state.currentView = "calendar";

    this.rootGroup = hmUI.createWidget(hmUI.widget.GROUP, {
      x: 0,
      y: 0,
      w: 390,
      h: 450
    });

    this.rootGroup.createWidget(hmUI.widget.TEXT, {
      x: LAYOUT.X,
      y: SAFE_TOP,
      w: LAYOUT.W,
      h: 40,
      text: "CALENDAR",
      color: COLORS.RED,
      text_size: FONT.HEADER,
      align_h: hmUI.align.CENTER_H
    });

    const calendar = data?.calendar || [];

    if (!calendar.length) {
      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: 0,
        y: 200,
        w: 390,
        h: 40,
        text: data?.error ? "ERROR LOADING" : "NO DATA",
        color: COLORS.WHITE,
        text_size: FONT.BODY,
        align_h: hmUI.align.CENTER_H
      });
      return;
    }

    const data_array = calendar.map(item => ({
      name: `${item.flag} ${item.name}`,
      date: item.date
    }));

    this.rootGroup.createWidget(hmUI.widget.SCROLL_LIST, {
      x: 0,
      y: 110,
      w: 390,
      h: 340,
      item_space: 6,
      item_config: [
        {
          type_id: 1,
          item_height: 54,
          item_bg_color: 0x111111,
          item_bg_radius: 10,
          text_view: [
            { x: 18, y: 4, w: 354, h: 26, key: 'name', color: COLORS.WHITE, text_size: 18 },
            { x: 18, y: 28, w: 354, h: 22, key: 'date', color: COLORS.GRAY, text_size: 16 }
          ],
          text_view_count: 2
        }
      ],
      item_config_count: 1,
      data_array: data_array,
      data_count: data_array.length,
      data_type_config: [{ start: 0, end: data_array.length - 1, type_id: 1 }],
      data_type_config_count: 1,
      item_click_func: (list, index) => {
        logger.log("Calendar item clicked:", index);
        this.renderEventDetail(calendar[index]);
      }
    });
  },

  renderEventDetail(race) {
    logger.log("renderEventDetail called");

    if (typeof display.setStayWake === "function") {
      display.setStayWake(true);
    }

    if (this.rootGroup) {
      hmUI.deleteWidget(this.rootGroup);
      this.rootGroup = null;
    }

    this.state.currentView = "event_detail";

    this.rootGroup = hmUI.createWidget(hmUI.widget.GROUP, {
      x: 0,
      y: 0,
      w: 390,
      h: 450
    });

    this.rootGroup.createWidget(hmUI.widget.TEXT, {
      x: LAYOUT.X,
      y: SAFE_TOP,
      w: LAYOUT.W,
      h: 70,
      text: `${race.flag} ${race.name}\n${race.circuit}`,
      color: COLORS.RED,
      text_size: 20,
      align_h: hmUI.align.CENTER_H
    });

    let y = 140;
    race.sessions.forEach(s => {
      const utcDate = new Date(s.time.replace("Z", ""));
      const localTime = `${utcDate.getHours().toString().padStart(2, "0")}:${utcDate.getMinutes().toString().padStart(2, "0")}`;
      const localDate = `${(utcDate.getMonth() + 1)}/${utcDate.getDate()}`;

      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: 40,
        y,
        w: 120,
        h: 26,
        text: s.name,
        color: COLORS.YELLOW,
        text_size: 18
      });

      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: 160,
        y,
        w: 190,
        h: 26,
        text: `${localDate}  ${localTime}`,
        color: COLORS.WHITE,
        text_size: 18,
        align_h: hmUI.align.RIGHT
      });

      y += 32;
    });
  },

  // =========================
  // STANDINGS UI
  // =========================
  renderStandings(data) {
    logger.log("renderStandings called");

    if (typeof display.setStayWake === "function") {
      display.setStayWake(true);
    }

    if (this.rootGroup) {
      hmUI.deleteWidget(this.rootGroup);
      this.rootGroup = null;
    }

    this.rootGroup = hmUI.createWidget(hmUI.widget.GROUP, {
      x: 0,
      y: 0,
      w: 390,
      h: 450
    });

    this.rootGroup.createWidget(hmUI.widget.TEXT, {
      x: LAYOUT.X,
      y: SAFE_TOP,
      w: LAYOUT.W,
      h: 40,
      text: "DRIVERS",
      color: COLORS.RED,
      text_size: FONT.HEADER,
      align_h: hmUI.align.CENTER_H
    });

    const standings = data?.standings || [];

    if (!standings.length) {
      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: 0,
        y: 200,
        w: 390,
        h: 40,
        text: data?.error ? "ERROR LOADING" : "NO STANDINGS",
        color: COLORS.WHITE,
        text_size: FONT.BODY,
        align_h: hmUI.align.CENTER_H
      });
      return;
    }

    const data_array = standings.map(item => ({
      pos: `${item.pos}`,
      name: `${item.flag} ${item.name}`,
      pts: `${item.points} pts`
    }));

    this.rootGroup.createWidget(hmUI.widget.SCROLL_LIST, {
      x: 0,
      y: 110,
      w: 390,
      h: 340,
      item_space: 6,
      item_config: [
        {
          type_id: 1,
          item_height: 46,
          item_bg_color: 0x000000,
          item_bg_radius: 0,
          text_view: [
            { x: 18, y: 8, w: 40, h: 30, key: 'pos', color: COLORS.WHITE, text_size: 18 },
            { x: 65, y: 6, w: 200, h: 30, key: 'name', color: COLORS.WHITE, text_size: 20, align_h: hmUI.align.LEFT },
            { x: 270, y: 10, w: 100, h: 30, key: 'pts', color: COLORS.YELLOW, text_size: 18, align_h: hmUI.align.RIGHT }
          ],
          text_view_count: 3
        }
      ],
      item_config_count: 1,
      data_array: data_array,
      data_count: data_array.length,
      data_type_config: [
        {
          start: 0,
          end: Math.max(0, data_array.length - 1),
          type_id: 1
        }
      ],
      data_type_config_count: 1
    });
  },

  // =========================
  // ERROR UI
  // =========================
  showError(message) {
    logger.log("SHOW_ERROR:", message);

    if (typeof display.setStayWake === "function") {
      display.setStayWake(false);
    }

    if (this.rootGroup) {
      hmUI.deleteWidget(this.rootGroup);
      this.rootGroup = null;
    }

    this.rootGroup = hmUI.createWidget(hmUI.widget.GROUP, {
      x: 0, y: 0, w: 390, h: 450
    });

    this.rootGroup.createWidget(hmUI.widget.TEXT, {
      x: 0, y: 150, w: 390, h: 50,
      text: "⚠️ CONNECTION ERROR",
      color: COLORS.RED,
      text_size: 24,
      align_h: hmUI.align.CENTER_H
    });

    this.rootGroup.createWidget(hmUI.widget.TEXT, {
      x: 20, y: 210, w: 350, h: 100,
      text: message,
      color: COLORS.WHITE,
      text_size: 20,
      text_style: hmUI.text_style.WRAP,
      align_h: hmUI.align.CENTER_H
    });

    this.rootGroup.createWidget(hmUI.widget.BUTTON, {
      x: 100, y: 320, w: 190, h: 50,
      text: "RETRY",
      normal_color: 0x333333,
      press_color: 0x666666,
      radius: 12,
      click_func: () => {
        this.fetchData();
      }
    });
  },

  // =========================
  // MAIN UI
  // =========================
  updateUI(data) {

    if (typeof display.setStayWake === "function") {
      display.setStayWake(true);
    }

    if (data?.error === "NO_INTERNET") {
      this.showError("The phone has no internet connection or the server is down.");
      return;
    }

    if (this.rootGroup) {
      hmUI.deleteWidget(this.rootGroup);
      this.rootGroup = null;
    }

    this.rootGroup = hmUI.createWidget(hmUI.widget.GROUP, {
      x: 0,
      y: 0,
      w: 390,
      h: 450
    });

    // REFRESH BUTTON
    this.rootGroup.createWidget(hmUI.widget.BUTTON, {
      x: 310, y: 10, w: 70, h: 40,
      text: this.state.testMode ? "SIM" : "REF",
      text_size: 16,
      normal_color: this.state.testMode ? 0x00FF00 : 0x333333,
      press_color: 0x666666,
      radius: 10,
      click_func: () => {
        this.fetchData();
      }
    });

    if (!data) {
      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: 0,
        y: 190,
        w: 390,
        h: 40,
        text: "SYNCING F1 DATA...",
        color: COLORS.WHITE,
        text_size: FONT.HEADER,
        align_h: hmUI.align.CENTER_H
      });
      return;
    }

    if (!data.live) {

      let y = SAFE_TOP;

      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: LAYOUT.X,
        y,
        w: LAYOUT.W,
        h: 40,
        text: "OFF SESSION",
        color: COLORS.GRAY,
        text_size: FONT.TITLE,
        align_h: hmUI.align.CENTER_H
      });


      y += 55;

      if (data.upcoming?.name) {
        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: LAYOUT.X,
          y,
          w: LAYOUT.W,
          h: 30,
          text: "NEXT RACE",
          color: COLORS.RED,
          text_size: FONT.HEADER,
          align_h: hmUI.align.CENTER_H
        });

        y += 32;

        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: LAYOUT.X,
          y,
          w: LAYOUT.W,
          h: 60,
          text: `${data.upcoming.flag || ""} ${data.upcoming.name}\n${data.upcoming.circuit || ""}`,
          color: COLORS.WHITE,
          text_size: 20,
          align_h: hmUI.align.CENTER_H
        });

        y += 62;

        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: LAYOUT.X,
          y,
          w: LAYOUT.W,
          h: 30,
          text: `${data.upcoming.date?.split("T")[0]}`,
          color: COLORS.GRAY,
          text_size: 18,
          align_h: hmUI.align.CENTER_H
        });

        y += 50;
      }

      if (data.previous?.name) {
        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: LAYOUT.X,
          y,
          w: LAYOUT.W,
          h: 30,
          text: "LAST RACE",
          color: COLORS.YELLOW,
          text_size: FONT.HEADER,
          align_h: hmUI.align.CENTER_H
        });

        y += 32;

        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: LAYOUT.X,
          y,
          w: LAYOUT.W,
          h: 60,
          text: `${data.previous.flag || ""} ${data.previous.name}\n${data.previous.circuit || ""}`,
          color: COLORS.WHITE,
          text_size: 20,
          align_h: hmUI.align.CENTER_H
        });

        y += 62;

        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: LAYOUT.X,
          y,
          w: LAYOUT.W,
          h: 30,
          text: `Winner: ${data.previous.winnerFlag || ""} ${data.previous.winner}`,
          color: COLORS.WHITE,
          text_size: 18,
          align_h: hmUI.align.CENTER_H
        });

        y += 28;

        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: LAYOUT.X,
          y,
          w: LAYOUT.W,
          h: 30,
          text: `${data.previous.team}`,
          color: data.previous.teamColor || COLORS.WHITE,
          text_size: 18,
          align_h: hmUI.align.CENTER_H
        });
      }

      return;
    }

    // LIVE
    let y = SAFE_TOP;

    this.rootGroup.createWidget(hmUI.widget.TEXT, {
      x: LAYOUT.X,
      y,
      w: 100,
      h: 40,
      text: "🔴 LIVE",
      color: COLORS.RED,
      text_size: 24,
      align_h: hmUI.align.LEFT
    });

    // Track Status
    let status_color = COLORS.WHITE;
    const status = data.track || "";
    if (status.includes("Yellow")) status_color = COLORS.YELLOW;
    else if (status.includes("Red")) status_color = COLORS.RED;
    else if (status.includes("Clear") || status.includes("Normal")) status_color = 0x00FF00;
    else if (status.includes("SC") || status.includes("Safety")) status_color = COLORS.YELLOW;

    this.rootGroup.createWidget(hmUI.widget.TEXT, {
      x: 120,
      y,
      w: 250,
      h: 40,
      text: status.toUpperCase(),
      color: status_color,
      text_size: 20,
      align_h: hmUI.align.RIGHT
    });

    y += 45;

    const timing_data = (data.timing || []).map(item => ({
      pos: `P${item.pos}`,
      name: item.name,
      color: parseInt(item.teamColor || "FFFFFF", 16),
      gap: item.gap || "",
      comp: item.comp ? `${item.comp.toLowerCase()}.png` : ""
    }));

    this.rootGroup.createWidget(hmUI.widget.SCROLL_LIST, {
      x: 0,
      y,
      w: 390,
      h: 450 - y,
      item_space: 6,
      item_config: [
        {
          type_id: 1,
          item_height: 50,
          item_bg_color: 0x111111,
          item_bg_radius: 8,
          text_view: [
            { x: 10, y: 10, w: 40, h: 30, key: 'pos', color: COLORS.WHITE, text_size: 18 },
            { x: 55, y: 8, w: 70, h: 32, key: 'name', color_key: 'color', text_size: 22, align_h: hmUI.align.LEFT },
            { x: 230, y: 12, w: 100, h: 26, key: 'gap', color: COLORS.GRAY, text_size: 16, align_h: hmUI.align.RIGHT }
          ],
          text_view_count: 3,
          image_view: [
            { x: 345, y: 13, w: 24, h: 24, key: 'comp' }
          ],
          image_view_count: 1
        }
      ],
      item_config_count: 1,
      data_array: timing_data,
      data_count: timing_data.length,
      data_type_config: [
        {
          start: 0,
          end: Math.max(0, timing_data.length - 1),
          type_id: 1
        }
      ],
      data_type_config_count: 1
    });
  }
}));
