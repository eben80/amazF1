AppSettingsPage({
  build(props) {
    return View({
      style: {
        padding: '20px'
      }
    }, [
      Text({
        style: {
          fontSize: '20px',
          fontWeight: 'bold'
        },
        value: 'F1 Live Timing Settings'
      }),
      Text({
        value: 'Bridge URL: http://ebski.co:8000/status'
      })
    ])
  }
})
