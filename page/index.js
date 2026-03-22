import * as hmUI from "@zos/ui";
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
    currentView: "main"
  },

  build() {

    logger.log("BUILD");

    // =========================
    // 1. INIT UI FIRST (LOWER LAYER)
    // =========================
    this.updateUI(null);
    this.fetchData();

    // =========================
    // 2. TOUCH LAYER LAST (TOP LAYER FIX)
    // =========================
    this.createTouchLayer();
  },

  // =========================
  // TOUCH LAYER (MUST BE LAST CREATED)
  // =========================
  createTouchLayer() {

    logger.log("TOUCH LAYER CREATED LAST");

    this.leftTap = hmUI.createWidget(hmUI.widget.BUTTON, {
      x: 0,
      y: 0,
      w: 195,
      h: 450,
      normal_color: 0x000000,
      press_color: 0x000000,
      text: "",

      click_func: () => {
        logger.log("LEFT TAP");

        if (this.state.currentView === "results") {
          this.state.currentView = "main";
          this.updateUI(this.state.f1Data);
        } else {
          this.loadResults();
        }
      }
    });

    this.rightTap = hmUI.createWidget(hmUI.widget.BUTTON, {
      x: 195,
      y: 0,
      w: 195,
      h: 450,
      normal_color: 0x000000,
      press_color: 0x000000,
      text: "",

      click_func: () => {
        logger.log("RIGHT TAP");
        this.fetchData();
      }
    });
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
    this.request({ method: "GET_RESULTS" })
      .then((res) => {
        // 'res' is the object returned from the side service
        // 'res.result' is the 'body' from your fetchStatus/fetchResults
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

  // =========================
  // RESULTS UI
  // =========================
  renderResults(data) {
    if (this.rootGroup) {
      hmUI.deleteWidget(this.rootGroup);
      this.rootGroup = null;
    }

    const results = data?.results || [];

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

    this.rootGroup.createWidget(hmUI.widget.SCROLL_LIST, {
      x: 0,
      y: 110,
      w: 390,
      h: 340,
      item_space: 6,
      item_count: results.length,

      item_creator: (list, index) => {
        const item = results[index];

        const group = list.createWidget(hmUI.widget.GROUP, {
          x: 0,
          y: 0,
          w: 390,
          h: 46
        });

        // Position (P1, P2, etc.)
        group.createWidget(hmUI.widget.TEXT, {
          x: 18,
          y: 8,
          w: 40,
          h: 30,
          text: `P${item.position}`,
          color: COLORS.WHITE,
          text_size: 18
        });

        // Driver Name - Using the flat properties from your Side Service
        group.createWidget(hmUI.widget.TEXT, {
          x: 70,
          y: 6,
          w: 180,
          h: 30,
          text: `${item.firstName} ${item.lastName}`,
          color: COLORS.WHITE,
          text_size: 20
        });

        // Points
        group.createWidget(hmUI.widget.TEXT, {
          x: 260,
          y: 10,
          w: 110,
          h: 30,
          text: `${item.points} pts`,
          color: COLORS.YELLOW,
          text_size: 18,
          align_h: hmUI.align.RIGHT
        });

        return group;
      }
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
        text: "F1 STATUS",
        color: COLORS.GRAY,
        text_size: FONT.TITLE,
        align_h: hmUI.align.CENTER_H
      });

      y += 40;

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

      y += 50;

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

        y += 30;

        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: LAYOUT.X,
          y,
          w: LAYOUT.W,
          h: 60,
          text: `${data.upcoming.name}\n${data.upcoming.date?.split("T")[0]}`,
          color: COLORS.WHITE,
          text_size: FONT.BODY,
          align_h: hmUI.align.CENTER_H
        });

        y += 70;
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

        y += 30;

        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: LAYOUT.X,
          y,
          w: LAYOUT.W,
          h: 60,
          text: `${data.previous.name}\nWinner: ${data.previous.winner}`,
          color: COLORS.WHITE,
          text_size: FONT.BODY,
          text_style: hmUI.text_style.WRAP,
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

    this.rootGroup.createWidget(hmUI.widget.SCROLL_LIST, {
      x: 0,
      y,
      w: 390,
      h: 450 - y,
      item_space: 6,
      item_count: (data.timing || []).length,

      item_creator: (list, index) => {

        const item = data.timing[index];

        const group = list.createWidget(hmUI.widget.GROUP, {
          x: 0,
          y: 0,
          w: 390,
          h: 44
        });

        group.createWidget(hmUI.widget.TEXT, {
          x: 18,
          y: 8,
          w: 40,
          h: 28,
          text: `P${item.pos}`,
          color: COLORS.WHITE,
          text_size: 18
        });

        group.createWidget(hmUI.widget.TEXT, {
          x: 70,
          y: 6,
          w: 180,
          h: 30,
          text: item.name,
          color: COLORS.WHITE,
          text_size: 20
        });

        return group;
      }
    });
  }
}));
