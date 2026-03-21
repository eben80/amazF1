import { BaseSideService } from "@zeppos/zml/base-side";

const BRIDGE_URL = "http://ebski.co:8000/status";

AppSideService(
  BaseSideService({
    async onRequest(req, res) {
      if (req.method === "GET_F1_DATA") {
        try {
          const response = await fetch({
            url: BRIDGE_URL,
            method: "GET",
          });

          const data =
            typeof response.body === "string"
              ? JSON.parse(response.body)
              : response.body;

          res(null, {
            result: data, // 👈 MUST be "result"
          });
        } catch (e) {
          res(null, {
            result: { error: e.message },
          });
        }
      }
    },
  })
);