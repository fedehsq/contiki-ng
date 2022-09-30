CONTIKI_PROJECT = coap-hello
all: $(CONTIKI_PROJECT)
CONTIKI = ../..

MAKE_NET_IPV6 = 1
MAKE_NET ?= MAKE_NET_IPV6
ifeq ($(MAKE_NET),MAKE_NET_IPV6)
CFLAGS += -DNETSTACK_CONF_WITH_IPV6=1
MODULES += $(CONTIKI_NG_NET_DIR)/ipv6
endif
# Default routing protocol: RPL for IPv6, None otherwise
ifeq ($(MAKE_NET),MAKE_NET_IPV6)
MAKE_ROUTING ?= MAKE_ROUTING_RPL_LITE
else
MAKE_ROUTING ?= MAKE_ROUTING_NULLROUTING
endif
# Include RPL BR module
include $(CONTIKI)/Makefile.dir-variables
MODULES += $(CONTIKI_NG_SERVICES_DIR)/rpl-border-router
MODULES += $(CONTIKI_NG_APP_LAYER_DIR)/coap
# Include webserver module
MODULES_REL += webserver
MODULES_REL += $(CONTIKI)/examples/my-coap-hello/resources
PROJECT_SOURCEFILES+=g_buf.c

# Include optional target-specific module
include $(CONTIKI)/Makefile.identify-target
MODULES_REL += $(TARGET)

include $(CONTIKI)/Makefile.include
