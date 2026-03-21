import { BaseSideService } from '@zeppos/zml/base-side'

const BRIDGE_URL = 'https://ebski.co/status'

AppSideService(
  BaseSideService({
    onInit() {
      console.log('AppSideService onInit')
    },

    async onRequest(req, res) {
      if (req.method === 'GET_F1_DATA') {
        try {
          const response = await fetch({
            url: BRIDGE_URL,
            method: 'GET'
          })

          const data = typeof response.body === 'string'
            ? JSON.parse(response.body)
            : response.body

          res(null, {
            result: data
          })
        } catch (e) {
          console.error('Fetch error:', e)
          res(null, {
            result: { error: e.message }
          })
        }
      }
    },

    onDestroy() {
      console.log('AppSideService onDestroy')
    }
  })
)
