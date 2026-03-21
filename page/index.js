import { BasePage } from '@zeppos/zml/base-page'

// Use global hmSetting for device info to avoid import resolution warnings in some CLI versions
const { width: DEVICE_WIDTH, height: DEVICE_HEIGHT } = hmSetting.getDeviceInfo()

const COLORS = {
  F1_RED: 0xFF1801,
  BLACK: 0x000000,
  WHITE: 0xFFFFFF,
  GRAY: 0x333333,
  YELLOW: 0xFFFF00
}

Page(
  BasePage({
    state: {
      f1Data: null,
      loading: true,
      error: null
    },

    onInit() {
      this.fetchData()
      this.timer = setInterval(() => this.fetchData(), 5000)
    },

    fetchData() {
      this.request({ action: 'FETCH_F1_DATA' })
    },

    onMessage(data) {
      if (data.action === 'F1_DATA_UPDATE') {
        this.setState({ f1Data: data.payload, loading: false, error: null })
        this.render()
      } else if (data.action === 'F1_DATA_ERROR') {
        this.setState({ error: 'Update failed', loading: false })
        this.render()
      }
    },

    build() {
      // Use global hmUI to avoid import resolution warnings
      hmUI.createWidget(hmUI.widget.FILL_RECT, { x: 0, y: 0, w: DEVICE_WIDTH, h: DEVICE_HEIGHT, color: COLORS.BLACK })
      this.render()
    },

    render() {
      if (this.rootGroup) hmUI.deleteWidget(this.rootGroup)
      this.rootGroup = hmUI.createWidget(hmUI.widget.GROUP, { x: 0, y: 0, w: DEVICE_WIDTH, h: DEVICE_HEIGHT })

      const data = this.state.f1Data
      if (this.state.loading) this.renderLoading()
      else if (!data || !data.live) this.renderIdle(data)
      else this.renderLive(data)
    },

    renderLoading() {
      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: 0, y: DEVICE_HEIGHT / 2 - 20, w: DEVICE_WIDTH, h: 40,
        text: 'Syncing F1 Data...', color: COLORS.WHITE, align_h: hmUI.align.CENTER_H, text_size: 20
      })
    },

    renderIdle(data) {
      if (data && data.previous && data.previous.name) {
        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: 0, y: 10, w: DEVICE_WIDTH, h: 30,
          text: 'PREVIOUS RACE', color: COLORS.GRAY, align_h: hmUI.align.CENTER_H, text_size: 16
        })
        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: 10, y: 40, w: DEVICE_WIDTH - 20, h: 60,
          text: `${data.previous.name}\nWinner: ${data.previous.winner}`,
          color: COLORS.WHITE, align_h: hmUI.align.CENTER_H, text_size: 18, text_style: hmUI.text_style.WRAP
        })
      }

      this.rootGroup.createWidget(hmUI.widget.FILL_RECT, {
        x: 40, y: 110, w: DEVICE_WIDTH - 80, h: 2, color: COLORS.F1_RED
      })

      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: 0, y: 125, w: DEVICE_WIDTH, h: 30,
        text: 'UPCOMING', color: COLORS.F1_RED, align_h: hmUI.align.CENTER_H, text_size: 20, text_style: hmUI.text_style.BOLD
      })

      if (data && data.upcoming && data.upcoming.name) {
        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: 20, y: 160, w: DEVICE_WIDTH - 40, h: 80,
          text: data.upcoming.name, color: COLORS.WHITE, align_h: hmUI.align.CENTER_H, text_size: 24, text_style: hmUI.text_style.WRAP
        })
        const dateStr = (data.upcoming.date || '').split('T')[0]
        if (dateStr) {
          this.rootGroup.createWidget(hmUI.widget.TEXT, {
            x: 0, y: 240, w: DEVICE_WIDTH, h: 40,
            text: dateStr, color: COLORS.YELLOW, align_h: hmUI.align.CENTER_H, text_size: 28, text_style: hmUI.text_style.BOLD
          })
        }
      } else {
        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: 0, y: DEVICE_HEIGHT / 2, w: DEVICE_WIDTH, h: 40,
          text: 'NO DATA', color: COLORS.GRAY, align_h: hmUI.align.CENTER_H, text_size: 20
        })
      }
    },

    renderLive(data) {
      this.rootGroup.createWidget(hmUI.widget.FILL_RECT, { x: 0, y: 0, w: DEVICE_WIDTH, h: 60, color: 0x111111 })
      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: 10, y: 10, w: DEVICE_WIDTH - 100, h: 24,
        text: data.session.name || 'LIVE', color: COLORS.WHITE, text_size: 20, text_style: hmUI.text_style.BOLD
      })
      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: 10, y: 35, w: DEVICE_WIDTH - 100, h: 20,
        text: `LAP ${data.laps.current}/${data.laps.total}`, color: COLORS.GRAY, text_size: 16
      })

      const statusColor = data.track === 'AllClear' ? 0x00FF00 : COLORS.YELLOW
      this.rootGroup.createWidget(hmUI.widget.TEXT, {
        x: DEVICE_WIDTH - 90, y: 15, w: 80, h: 30,
        text: data.track, color: statusColor, align_h: hmUI.align.CENTER_H, text_size: 16, text_style: hmUI.text_style.BOLD
      })

      const timing = data.timing || []
      timing.forEach((item, index) => {
        const yPos = 70 + (index * 35)
        if (yPos > DEVICE_HEIGHT - 35) return

        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: 5, y: yPos, w: 25, h: 30, text: item.pos, color: COLORS.WHITE, text_size: 18
        })
        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: 35, y: yPos, w: 60, h: 30, text: item.name, color: parseInt(item.col, 16) || COLORS.WHITE, text_size: 18, text_style: hmUI.text_style.BOLD
        })

        if (item.comp) {
          let tireImg = 'soft.png'
          if (item.comp === 'MEDIUM') tireImg = 'medium.png'
          else if (item.comp === 'HARD') tireImg = 'hard.png'
          this.rootGroup.createWidget(hmUI.widget.IMG, {
            x: 100, y: yPos + 4, src: tireImg
          })
        }

        this.rootGroup.createWidget(hmUI.widget.TEXT, {
          x: 125, y: yPos, w: DEVICE_WIDTH - 130, h: 30,
          text: item.gap || '+0.000', color: COLORS.GRAY, align_h: hmUI.align.RIGHT, text_size: 16
        })
      })
    },

    onDestroy() {
      if (this.timer) clearInterval(this.timer)
    }
  })
)
