import * as hmUI from "@zos/ui";
import { BasePage } from "@zeppos/zml/base-page";

let textWidget;

Page(
  BasePage({
    build() {
      hmUI.createWidget(hmUI.widget.BUTTON, {
        x: 40,
        y: 50,
        w: 200,
        h: 50,
        text: "Fetch F1",
        click_func: () => {
          this.fetchData();
        },
      });
    },

    fetchData() {
      this.request({
        method: "GET_F1_DATA", // 👈 MUST match app-side
      })
        .then((data) => {
          const { result } = data;

          const text = result?.live
            ? "LIVE RACE"
            : result?.upcoming?.name || "NO DATA";

          if (!textWidget) {
            textWidget = hmUI.createWidget(hmUI.widget.TEXT, {
              x: 10,
              y: 120,
              w: 300,
              h: 100,
              text,
              text_size: 20,
              color: 0xffffff,
            });
          } else {
            textWidget.setProperty(hmUI.prop.TEXT, text);
          }
        })
        .catch((err) => {
          console.log("ERROR:", err);
        });
    },
  })
);