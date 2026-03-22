import { BaseApp } from '@zeppos/zml/base-app'

App(
  BaseApp({
    globalData: {
      raceState: null,
      weather: null,
      session: null
    },
    onCreate(options) {
      console.log('App onCreate')
    },
    onDestroy(options) {
      console.log('App onDestroy')
    }
  })
)
