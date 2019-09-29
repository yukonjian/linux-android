struct snd_pcm_hw_params {
	unsigned int flags;
	struct snd_mask masks[SNDRV_PCM_HW_PARAM_LAST_MASK -
			       SNDRV_PCM_HW_PARAM_FIRST_MASK + 1];
	struct snd_mask mres[5];	/* reserved masks */
	struct snd_interval intervals[SNDRV_PCM_HW_PARAM_LAST_INTERVAL -
				        SNDRV_PCM_HW_PARAM_FIRST_INTERVAL + 1];
	struct snd_interval ires[9];	/* reserved intervals */
	unsigned int rmask;		/* W: requested masks */
	unsigned int cmask;		/* R: changed masks */
	unsigned int info;		/* R: Info flags for returned setup */
	unsigned int msbits;		/* R: used most significant bits */
	unsigned int rate_num;		/* R: rate numerator */
	unsigned int rate_den;		/* R: rate denominator */
	snd_pcm_uframes_t fifo_size;	/* R: chip FIFO size in frames */
	unsigned char reserved[64];	/* reserved for future */
};

enum {
	SNDRV_PCM_TSTAMP_NONE = 0,
	SNDRV_PCM_TSTAMP_ENABLE,
	SNDRV_PCM_TSTAMP_LAST = SNDRV_PCM_TSTAMP_ENABLE,
};

struct snd_pcm_sw_params {
	int tstamp_mode;			/* timestamp mode */
	unsigned int period_step;
	unsigned int sleep_min;			/* min ticks to sleep */
	snd_pcm_uframes_t avail_min;		/* min avail frames for wakeup */
	snd_pcm_uframes_t xfer_align;		/* obsolete: xfer size need to be a multiple */
	snd_pcm_uframes_t start_threshold;	/* min hw_avail frames for automatic start */
	snd_pcm_uframes_t stop_threshold;	/* min avail frames for automatic stop */
	snd_pcm_uframes_t silence_threshold;	/* min distance from noise for silence filling */
	snd_pcm_uframes_t silence_size;		/* silence block size */
	snd_pcm_uframes_t boundary;		/* pointers wrap point */
	unsigned int proto;			/* protocol version */
	unsigned int tstamp_type;		/* timestamp type (req. proto >= 2.0.12) */
	unsigned char reserved[56];		/* reserved for future */
};

inclue/pcm.h
src/pcm/pcm.c
src/pcm/pcm_hw.c
