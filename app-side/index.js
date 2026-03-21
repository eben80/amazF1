import { BaseSideService } from '@zeppos/zml/base-side'

// Using HTTPS for secure communication as requested
const BRIDGE_URL = 'https://ebski.co/status'

AppSideService(
  BaseSideService({
    onInit() {
      console.log('AppSideService onInit')
    },

    async onMessage(message) {
      if (message.action === 'FETCH_F1_DATA') {
        try {
          const response = await fetch(BRIDGE_URL)
          const data = await response.json()

          this.sendToDevice({
            action: 'F1_DATA_UPDATE',
            payload: data
          })
        } catch (e) {
          console.error('Fetch error:', e)
          this.sendToDevice({
            action: 'F1_DATA_ERROR',
            payload: e.message
          })
        }
      }
    },

    onDestroy() {
      console.log('AppSideService onDestroy')
    }
  })
)
