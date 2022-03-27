/**
 * \file curl.h
 * \brief libcurl calls
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */
#ifndef __CURL_H__
#define __CURL_H__

#include <curl/curl.h>
#include "buffer.h"

/**
 * \brief libcurl network timeout
 */
#define CURL_EXECUTE_TIMEOUT    60

/**
 * \fn curl_execute(const char* psz_url, ps_buffer p_buffer)
 * \brief execution of a GET by libcurl
 *
 * \param psz_url GET url
 * \param p_buffer struct s_buffer to receive returned datas
 * \return 1:Ok, 0:Ko
 */
int    curl_execute(const char* psz_url, ps_buffer p_buffer);

#endif /* __CURL_H__ */

