/**
 * \file curl.c
 * \brief libcurl calls
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */
#include "curl.h"

/**
 * \fn curl_to_buffer(void* pv_curl_data, size_t curl_data_size, size_t curl_data_nmemb, void* udata)
 * \brief callback used by libcurl to append received datas to struct s_buffer
 *
 * \param pv_curl_data datas received
 * \param curl_data_size size of one element received
 * \param curl_data_nmemb nb elements of size curl_data_size
 * \param udata struct s_buffer which receives the data
 * \return len of data copied (curl_data_size * curl_data_nmemb)
 */
size_t
curl_to_buffer(void* pv_curl_data, size_t curl_data_size, size_t curl_data_nmemb, void* udata) ;

/**
 * \brief libcurl network timeout
 */
u_int16_t    curl_execute_timeout;

/**
 * \fn curl_execute(const char* psz_url, ps_buffer p_buffer)
 * \brief execution of a GET by libcurl
 *
 * \param psz_url GET url
 * \param p_buffer struct s_buffer to receive returned datas
 * \return 1:Ok, 0:Ko
 */
int    curl_execute(const char* psz_url, ps_buffer p_buffer) {
    CURL*    p_curl;
    char     buffer_error[CURL_ERROR_SIZE];

    char*    curl_url;
    long     response_code;
    double   elapsed;

    curl_execute_timeout = CURL_EXECUTE_TIMEOUT ;

    p_curl = curl_easy_init() ;
    if ( p_curl != NULL ) {
        curl_easy_setopt(p_curl, CURLOPT_WRITEDATA, p_buffer);
        curl_easy_setopt(p_curl, CURLOPT_WRITEFUNCTION, curl_to_buffer);

        curl_easy_setopt(p_curl, CURLOPT_URL, psz_url) ;

        curl_easy_setopt(p_curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(p_curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(p_curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(p_curl, CURLOPT_USERAGENT, "netatmo-grabber/1.0");
        curl_easy_setopt(p_curl, CURLOPT_TIMEOUT, curl_execute_timeout);
        curl_easy_setopt(p_curl, CURLOPT_ERRORBUFFER, buffer_error) ;

        curl_easy_getinfo(p_curl, CURLINFO_RESPONSE_CODE, &response_code);
        curl_easy_getinfo(p_curl, CURLINFO_TOTAL_TIME, &elapsed);
        curl_easy_getinfo(p_curl, CURLINFO_EFFECTIVE_URL, &curl_url);

        curl_easy_perform(p_curl);
        
        curl_easy_cleanup(p_curl);
        return 1 ;
    }
    return 0;
}

/**
 * \fn curl_to_buffer(void* pv_curl_data, size_t curl_data_size, size_t curl_data_nmemb, void* udata)
 * \brief callback used by libcurl to append received datas to struct s_buffer
 *
 * \param pv_curl_data datas received
 * \param curl_data_size size of one element received
 * \param curl_data_nmemb nb elements of size curl_data_size
 * \param udata struct s_buffer which receives the data
 * \return len of data copied (curl_data_size * curl_data_nmemb)
 */
size_t
curl_to_buffer(void* pv_curl_data, size_t curl_data_size, size_t curl_data_nmemb, void* udata) {
    size_t     len ;
    ps_buffer  p_buffer ;

    len = curl_data_size * curl_data_nmemb ;
    p_buffer = (ps_buffer) udata ;
    buffer_append(p_buffer, pv_curl_data, len);
    return len;
}


