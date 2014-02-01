# Target specific macros
TARGET = mainSW502E13

TARGET_SOURCES := \
main.c \
nxt_interface.c \
controller.c \
abs.c \
aeb.c \
speedometer.c \
datalog.c \
eaeb.c \
laneControl.c \
tcs.c \
edc.c \
acc.c \
sonar.c

TOPPERS_OSEK_OIL_SOURCE := ./main.oil

BUILD_MDOE = RXE_ONLY

O_PATH ?= build

include ../../ecrobot/ecrobot.mak

