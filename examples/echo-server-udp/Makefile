CONTIKI_PROJECT = udp
all: $(CONTIKI_PROJECT)

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

CONTIKI = ../..
include $(CONTIKI)/Makefile.include
