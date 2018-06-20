﻿/**
 * File:   input_method.h
 * Author: AWTK Develop Team
 * Brief:  input method interface.
 *
 * Copyright (c) 2018 - 2018  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-06-19 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "base/input_method.h"

ret_t input_method_dispatch(input_method_t* im, event_t* e) {
  return_value_if_fail(im != NULL && e != NULL, RET_BAD_PARAMS);

  return emitter_dispatch(&(im->emitter), e);
}

ret_t input_method_dispatch_to_widget(input_method_t* im, event_t* e) {
  return_value_if_fail(im != NULL && im->widget != NULL && e != NULL, RET_BAD_PARAMS);

  e->target = im->widget;
  return widget_dispatch(im->widget, e);
}

uint32_t input_method_on(input_method_t* im, event_type_t type, event_func_t on_event, void* ctx) {
  return_value_if_fail(im != NULL && on_event != NULL, 0);

  return emitter_on(&(im->emitter), type, on_event, ctx);
}

ret_t input_method_off(input_method_t* im, uint32_t id) {
  return_value_if_fail(im != NULL, RET_BAD_PARAMS);

  return emitter_off(&(im->emitter), id);
}

ret_t input_method_request(input_method_t* im, widget_t* widget) {
  return_value_if_fail(im != NULL && im->request != NULL, RET_BAD_PARAMS);

  return im->request(im, widget);
}

static input_method_t* s_input_method = NULL;
input_method_t* input_method(void) {
  return s_input_method;
}

ret_t input_method_set(input_method_t* im) {
  s_input_method = im;

  return RET_OK;
}