1. kernel\drivers\gpu\drm\rockchip\rockchip_vop_reg.c

static const struct vop_win_data rk3366_vop_lit_win_data[] = {

		{ .base = 0x00, .phy = &rk3366_lit_win1_data,
	  .type = DRM_PLANE_TYPE_PRIMARY },

	  	{ .base = 0x00, .phy = &rk3366_lit_win0_data,
	  .type = DRM_PLANE_TYPE_CURSOR },
};

kernel\drivers\gpu\drm\rockchip\rockchip_drm_vop.c
static int vop_crtc_atomic_check(struct drm_crtc *crtc,
				 struct drm_crtc_state *crtc_state)
{
	sort(pzpos, cnt, sizeof(pzpos[0]), vop_zpos_cmp, NULL);

	for (i = 0, cnt = 0; i < vop_data->win_size; i++) {
		const struct vop_win_data *win_data = &vop_data->win[i];
		int shift = i * 2;

		if (win_data->phy) {
			struct vop_zpos *zpos = &pzpos[cnt++];

			dsp_layer_sel |= zpos->win_id << shift;
		} else {
			dsp_layer_sel |= i << shift;
		}
	}

	/* add by steven;由于RK的算法的出的dsp_layer_sel为4; 但是我们需要将win1设置为primary,故这里将dsp_layer_sel设置为1，
	 * win0在win1的上面;
	*/
	dsp_layer_sel = 1;

	s->dsp_layer_sel = dsp_layer_sel;

	vop_dclk_source_generate(crtc, crtc_state);

err_free_pzpos:
	kfree(pzpos);
	return ret;
}

2. 背光修改
	 Symbol: BACKLIGHT_PWM [=n]                                                                                                                                                     |
  | Type  : tristate                                                                                                                                                               |
  | Prompt: Generic PWM based Backlight Driver                                                                                                                                     |
  |   Location:                                                                                                                                                                    |
  |     -> Device Drivers                                                                                                                                                          |
  |       -> Graphics support                                                                                                                                                      |
  |         -> Backlight & LCD device support (BACKLIGHT_LCD_SUPPORT [=y])                                                                                                         |
  | (2)       -> Lowlevel Backlight controls (BACKLIGHT_CLASS_DEVICE [=y])                                                                                                         |
  |   Defined at drivers/video/backlight/Kconfig:261                                                                                                                               |
  |   Depends on: HAS_IOMEM [=y] && BACKLIGHT_LCD_SUPPORT [=y] && BACKLIGHT_CLASS_DEVICE [=y] && PWM [=y]

	/sys/class/backlight/backlight/brightness


ln -s /bin/dsp /tmp/dsp
ln -s /basic/voice_dsp.ini /tmp/voice_dsp.ini
/tmp/dsp /tmp 20 2 0 &
