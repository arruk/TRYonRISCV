ACTIVE_PIPELINES := 1
EXTRA_DEFINES :=

ifneq ($(filter torv3 torv4 torv4p1 torv5 torv5p1 torv6,$(CORE)),)
	PREDICTION_MASK := 1
else
	PREDICTION_MASK := 0
endif

