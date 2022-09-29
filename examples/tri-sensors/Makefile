CONTIKI_PROJECT = coap-hello
all: $(CONTIKI_PROJECT)
CONTIKI = ../..


# Include RPL BR module
include $(CONTIKI)/Makefile.dir-variables
MODULES += $(CONTIKI_NG_SERVICES_DIR)/rpl-border-router
MODULES += $(CONTIKI_NG_APP_LAYER_DIR)/coap
# Include webserver module
MODULES_REL += webserver
MODULES_REL += $(CONTIKI)/examples/my-coap-hello/resources

# Include optional target-specific module
include $(CONTIKI)/Makefile.identify-target
MODULES_REL += $(TARGET)

include $(CONTIKI)/Makefile.include
