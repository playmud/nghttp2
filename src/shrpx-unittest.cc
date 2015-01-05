/*
 * nghttp2 - HTTP/2 C Library
 *
 * Copyright (c) 2013 Tatsuhiro Tsujikawa
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
// include test cases' include files here
#include "shrpx_ssl_test.h"
#include "shrpx_downstream_test.h"
#include "shrpx_config_test.h"
#include "http2_test.h"
#include "util_test.h"
#include "nghttp2_gzip_test.h"
#include "ringbuf_test.h"
#include "shrpx_config.h"

static int init_suite1(void) { return 0; }

static int clean_suite1(void) { return 0; }

int main(int argc, char *argv[]) {
  CU_pSuite pSuite = NULL;
  unsigned int num_tests_failed;

  OpenSSL_add_all_algorithms();
  SSL_load_error_strings();
  SSL_library_init();

  shrpx::create_config();

  // initialize the CUnit test registry
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  // add a suite to the registry
  pSuite = CU_add_suite("shrpx_TestSuite", init_suite1, clean_suite1);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // add the tests to the suite
  if (!CU_add_test(pSuite, "ssl_create_lookup_tree",
                   shrpx::test_shrpx_ssl_create_lookup_tree) ||
      !CU_add_test(pSuite, "ssl_cert_lookup_tree_add_cert_from_file",
                   shrpx::test_shrpx_ssl_cert_lookup_tree_add_cert_from_file) ||
      !CU_add_test(pSuite, "http2_add_header", shrpx::test_http2_add_header) ||
      !CU_add_test(pSuite, "http2_get_header", shrpx::test_http2_get_header) ||
      !CU_add_test(pSuite, "http2_copy_headers_to_nva",
                   shrpx::test_http2_copy_headers_to_nva) ||
      !CU_add_test(pSuite, "http2_build_http1_headers_from_headers",
                   shrpx::test_http2_build_http1_headers_from_headers) ||
      !CU_add_test(pSuite, "http2_lws", shrpx::test_http2_lws) ||
      !CU_add_test(pSuite, "http2_rewrite_location_uri",
                   shrpx::test_http2_rewrite_location_uri) ||
      !CU_add_test(pSuite, "http2_parse_http_status_code",
                   shrpx::test_http2_parse_http_status_code) ||
      !CU_add_test(pSuite, "http2_index_header",
                   shrpx::test_http2_index_header) ||
      !CU_add_test(pSuite, "http2_lookup_token",
                   shrpx::test_http2_lookup_token) ||
      !CU_add_test(pSuite, "http2_check_http2_pseudo_header",
                   shrpx::test_http2_check_http2_pseudo_header) ||
      !CU_add_test(pSuite, "http2_http2_header_allowed",
                   shrpx::test_http2_http2_header_allowed) ||
      !CU_add_test(pSuite, "http2_mandatory_request_headers_presence",
                   shrpx::test_http2_mandatory_request_headers_presence) ||
      !CU_add_test(pSuite, "downstream_index_request_headers",
                   shrpx::test_downstream_index_request_headers) ||
      !CU_add_test(pSuite, "downstream_index_response_headers",
                   shrpx::test_downstream_index_response_headers) ||
      !CU_add_test(pSuite, "downstream_get_request_header",
                   shrpx::test_downstream_get_request_header) ||
      !CU_add_test(pSuite, "downstream_get_response_header",
                   shrpx::test_downstream_get_response_header) ||
      !CU_add_test(pSuite, "downstream_crumble_request_cookie",
                   shrpx::test_downstream_crumble_request_cookie) ||
      !CU_add_test(pSuite, "downstream_assemble_request_cookie",
                   shrpx::test_downstream_assemble_request_cookie) ||
      !CU_add_test(pSuite, "downstream_rewrite_location_response_header",
                   shrpx::test_downstream_rewrite_location_response_header) ||
      !CU_add_test(pSuite, "config_parse_config_str_list",
                   shrpx::test_shrpx_config_parse_config_str_list) ||
      !CU_add_test(pSuite, "config_parse_header",
                   shrpx::test_shrpx_config_parse_header) ||
      !CU_add_test(pSuite, "config_parse_log_format",
                   shrpx::test_shrpx_config_parse_log_format) ||
      !CU_add_test(pSuite, "util_streq", shrpx::test_util_streq) ||
      !CU_add_test(pSuite, "util_strieq", shrpx::test_util_strieq) ||
      !CU_add_test(pSuite, "util_inp_strlower",
                   shrpx::test_util_inp_strlower) ||
      !CU_add_test(pSuite, "util_to_base64", shrpx::test_util_to_base64) ||
      !CU_add_test(pSuite, "util_percent_encode_token",
                   shrpx::test_util_percent_encode_token) ||
      !CU_add_test(pSuite, "util_quote_string",
                   shrpx::test_util_quote_string) ||
      !CU_add_test(pSuite, "util_utox", shrpx::test_util_utox) ||
      !CU_add_test(pSuite, "util_http_date", shrpx::test_util_http_date) ||
      !CU_add_test(pSuite, "util_select_h2", shrpx::test_util_select_h2) ||
      !CU_add_test(pSuite, "gzip_inflate", test_nghttp2_gzip_inflate) ||
      !CU_add_test(pSuite, "ringbuf_write", nghttp2::test_ringbuf_write) ||
      !CU_add_test(pSuite, "ringbuf_iovec", nghttp2::test_ringbuf_iovec)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Run all tests using the CUnit Basic interface
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  num_tests_failed = CU_get_number_of_tests_failed();
  CU_cleanup_registry();
  if (CU_get_error() == CUE_SUCCESS) {
    return num_tests_failed;
  } else {
    printf("CUnit Error: %s\n", CU_get_error_msg());
    return CU_get_error();
  }
}
