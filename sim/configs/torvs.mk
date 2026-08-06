ACTIVE_PIPELINES := 3

STORE_B  ?= 0
LOAD_B   ?= 0
BRANCH_B ?= 0
RAS      ?= 0

ifeq ($(BRANCH_B),1)
	override LOAD_B  := 1
	override STORE_B := 1
endif

ifeq ($(LOAD_B),1)
	override STORE_B := 1
endif

EXTRA_DEFINES :=

ifeq ($(STORE_B),1)
	EXTRA_DEFINES += STORE_IN_B
endif

ifeq ($(LOAD_B),1)
	EXTRA_DEFINES += LOAD_IN_B
endif

ifeq ($(RAS),1)
	EXTRA_DEFINES += CONFIG_RAS
endif

ifeq ($(BRANCH_B),1)
	EXTRA_DEFINES += BTYPE_IN_B
endif

ifeq ($(CORE),torvs5C)
	PREDICTION_MASK := 0
else ifeq ($(BRANCH_B),1)
	PREDICTION_MASK := 3
else
	PREDICTION_MASK := 1
endif

