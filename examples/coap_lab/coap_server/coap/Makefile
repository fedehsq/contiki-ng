CONTIKI_PROJECT = coap-server
all: $(CONTIKI_PROJECT)
CONTIKI = ../..

MODULES_REL += ./../resources



MODULES += $(CONTIKI_NG_APP_LAYER_DIR)/coap


# Include optional target-specific module
include $(CONTIKI)/Makefile.identify-target
MODULES_REL += $(TARGET)

include $(CONTIKI)/Makefile.include
