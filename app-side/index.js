import { BaseSideService } from "@zeppos/zml/base-side";

// =========================
// FETCH LIVE STATUS
// =========================
async function fetchStatus(res) {
  try {
    const response = await fetch({
      url: 'http://ebski.co:8000/status',
      method: 'GET'
    });

    const body = typeof response.body === 'string'
      ? JSON.parse(response.body)
      : response.body;

    console.log("FETCH_RESULTS_BODY:", JSON.stringify(body).substring(0, 200));
    res(null, { result: body });

  } catch (error) {
    console.log("FETCH_RESULTS_ERROR:", error);
    res(null, { result: { error: true } });
  }
}

// =========================
// FETCH STANDINGS
// =========================
async function fetchStandings(res) {
  try {
    const response = await fetch({
      url: 'http://ebski.co:8000/standings',
      method: 'GET'
    });

    const body = typeof response.body === 'string'
      ? JSON.parse(response.body)
      : response.body;

    console.log("FETCH_STANDINGS_BODY:", JSON.stringify(body).substring(0, 200));
    res(null, { result: body });

  } catch (error) {
    console.log("FETCH_STANDINGS_ERROR:", error);
    res(null, { result: { error: true } });
  }
}

// =========================
// FETCH PREVIOUS RESULTS
// =========================
async function fetchResults(res) {
  try {
    const response = await fetch({
      url: 'http://ebski.co:8000/previous_results',
      method: 'GET'
    });

    const body = typeof response.body === 'string'
      ? JSON.parse(response.body)
      : response.body;

    res(null, { result: body });

  } catch (error) {
    res(null, { result: { error: true } });
  }
}

// =========================
// SERVICE
// =========================
AppSideService(
  BaseSideService({
    onRequest(req, res) {

      if (req.method === "GET_DATA") {
        fetchStatus(res);
      }

      if (req.method === "GET_RESULTS") {
        fetchResults(res);
      }

      if (req.method === "GET_STANDINGS") {
        fetchStandings(res);
      }
    }
  })
);
