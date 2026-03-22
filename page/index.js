import * as hmUI from "@zos/ui";
import * as display from "@zos/display";
import { getDeviceInfo } from "@zos/device";
import { onGesture, GESTURE_LEFT, GESTURE_RIGHT } from "@zos/interaction";
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
    currentView: "main"
  },

  onInit() {
    if (typeof display.setStayWake === "function") {
      display.setStayWake(true);
    } else {
      logger.log("display.setStayWake not found");
    }

    const { width } = getDeviceInfo();
    this.state.DEVICE_WIDTH = width;

    onGesture({
      callback: (event) => {
        logger.log("GESTURE EVENT:", event);

        if (event === GESTURE_LEFT) {
          if (this.state.currentView === "main") {
            hmUI.showToast({ text: "Results" });
            this.loadResults();
            return true;
          } else if (this.state.currentView === "results") {
            hmUI.showToast({ text: "Standings" });
            this.loadStandings();
            return true;
          }
        }

        if (event === GESTURE_RIGHT) {
          if (this.state.currentView === "results") {
            this.state.currentView = "main";
            this.updateUI(this.state.f1Data);
            return true;
          } else if (this.state.currentView === "standings") {
            this.loadResults();
            return true;
          }
        }

        return false;
      }
    });
  },

  onDestroy() {
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
    this.request({ method: "GET_DATA" })
      .then((res) => {
        this.state.f1Data = res?.result;
        this.updateUI(this.state.f1Data);
      })
      .catch(() => {
        this.updateUI({ error: true });
      });
  },

  loadResults() {
    logger.log("loadResults called");
    this.request({ method: "GET_RESULTS" })
      .then((res) => {
        logger.log("loadResults success:", JSON.stringify(res).substring(0, 200));
        const data = res?.result;

        if (data && data.results) {
          this.state.resultsData = data;
          this.state.currentView = "results";
          this.renderResults(data);
        } else {
          logger.log("Data received but results missing");
          this.renderResults({ raceName: "No Data", results: [] });
        }
      })
      .catch((err) => {
        logger.log("Request failed", err);
        this.renderResults({ raceName: "Error", results: [] });
      });
  },

  loadStandings() {
    logger.log("loadStandings called");
    this.request({ method: "GET_STANDINGS" })
      .then((res) => {
        logger.log("loadStandings success:", JSON.stringify(res).substring(0, 200));
        const data = res?.result;

        if (data && data.standings) {
          this.state.currentView = "standings";
          this.renderStandings(data);
        } else {
          logger.log("Data received but standings missing");
          this.renderStandings({ standings: [] });
        }
      })
      .catch((err) => {
        logger.log("Request failed", err);
        this.renderStandings({ error: true });
      });
  },

  // =========================
  // RESULTS UI
  // =========================
  renderResults(data) {
    logger.log("renderResults called with data:", JSON.stringify(data).substring(0, 200));
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
  // STANDINGS UI
  // =========================
  renderStandings(data) {
    logger.log("renderStandings called");
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
      text: "STANDINGS",
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
      pts: `${item.points}`
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
  // MAIN UI
  // =========================
  updateUI(data) {

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
          h: 60,
          text: `NEXT: ${data.upcoming.flag || ""} ${data.upcoming.name}\n${data.upcoming.circuit || ""}`,
          color: COLORS.RED,
          text_size: FONT.HEADER,
          align_h: hmUI.align.CENTER_H
        });

        y += 62;

        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: LAYOUT.X,
          y,
          w: LAYOUT.W,
          h: 30,
          text: `${data.upcoming.date?.split("T")[0]}`,
          color: COLORS.WHITE,
          text_size: FONT.BODY,
          align_h: hmUI.align.CENTER_H
        });

        y += 60;
      }

      if (data.previous?.name) {
        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: LAYOUT.X,
          y,
          w: LAYOUT.W,
          h: 60,
          text: `LAST: ${data.previous.flag || ""} ${data.previous.name}\n${data.previous.circuit || ""}`,
          color: COLORS.YELLOW,
          text_size: FONT.HEADER,
          align_h: hmUI.align.CENTER_H
        });

        y += 62;

        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: LAYOUT.X,
          y,
          w: LAYOUT.W,
          h: 60,
          text: `Winner: ${data.previous.winnerFlag || ""} ${data.previous.winner}`,
          color: COLORS.WHITE,
          text_size: FONT.BODY,
          align_h: hmUI.align.CENTER_H
        });

        y += 30;

        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: LAYOUT.X,
          y,
          w: LAYOUT.W,
          h: 30,
          text: `${data.previous.team}`,
          color: data.previous.teamColor || COLORS.WHITE,
          text_size: FONT.BODY,
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
      w: LAYOUT.W,
      h: 40,
      text: "🔴 LIVE SESSION",
      color: COLORS.RED,
      text_size: FONT.TITLE,
      align_h: hmUI.align.CENTER_H
    });

    y += 45;

    const timing_data = (data.timing || []).map(item => ({
      pos: `P${item.pos}`,
      name: item.name
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
          item_height: 44,
          item_bg_color: 0x000000,
          item_bg_radius: 0,
          text_view: [
            { x: 18, y: 8, w: 40, h: 28, key: 'pos', color: COLORS.WHITE, text_size: 18 },
            { x: 70, y: 6, w: 180, h: 30, key: 'name', color: COLORS.WHITE, text_size: 20 }
          ],
          text_view_count: 2
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
