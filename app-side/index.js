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

    if (!response || !response.body) {
      res(null, { result: { error: "NO_INTERNET" } });
      return;
    }

    const body = typeof response.body === 'string'
      ? JSON.parse(response.body)
      : response.body;

    res(null, { result: body });

  } catch (error) {
    console.log("FETCH_STATUS_ERROR:", error);
    res(null, { result: { error: "NO_INTERNET" } });
  }
}

// =========================
// FETCH CALENDAR
// =========================
async function fetchCalendar(res) {
  try {
    const response = await fetch({
      url: 'http://ebski.co:8000/calendar',
      method: 'GET'
    });

    if (!response || !response.body) {
      res(null, { result: { error: "NO_INTERNET" } });
      return;
    }

    const body = typeof response.body === 'string'
      ? JSON.parse(response.body)
      : response.body;

    res(null, { result: body });

  } catch (error) {
    console.log("FETCH_CALENDAR_ERROR:", error);
    res(null, { result: { error: "NO_INTERNET" } });
  }
}

// =========================
// FETCH CONSTRUCTOR STANDINGS
// =========================
async function fetchConstructorStandings(res) {
  try {
    const response = await fetch({
      url: 'http://ebski.co:8000/constructor_standings',
      method: 'GET'
    });

    if (!response || !response.body) {
      res(null, { result: { error: "NO_INTERNET" } });
      return;
    }

    const body = typeof response.body === 'string'
      ? JSON.parse(response.body)
      : response.body;

    res(null, { result: body });

  } catch (error) {
    console.log("FETCH_CONSTRUCTORS_ERROR:", error);
    res(null, { result: { error: "NO_INTERNET" } });
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

    if (!response || !response.body) {
      res(null, { result: { error: "NO_INTERNET" } });
      return;
    }

    const body = typeof response.body === 'string'
      ? JSON.parse(response.body)
      : response.body;

    res(null, { result: body });

  } catch (error) {
    console.log("FETCH_STANDINGS_ERROR:", error);
    res(null, { result: { error: "NO_INTERNET" } });
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

    if (!response || !response.body) {
      res(null, { result: { error: "NO_INTERNET" } });
      return;
    }

    const body = typeof response.body === 'string'
      ? JSON.parse(response.body)
      : response.body;

    res(null, { result: body });

  } catch (error) {
    console.log("FETCH_RESULTS_ERROR:", error);
    res(null, { result: { error: "NO_INTERNET" } });
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

      if (req.method === "GET_CONSTRUCTOR_STANDINGS") {
        fetchConstructorStandings(res);
      }

      if (req.method === "GET_CALENDAR") {
        fetchCalendar(res);
      }
    }
  })
);
