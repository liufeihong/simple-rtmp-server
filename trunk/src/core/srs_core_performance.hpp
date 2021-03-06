/*
The MIT License (MIT)

Copyright (c) 2013-2014 winlin

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef SRS_CORE_PERFORMANCE_HPP
#define SRS_CORE_PERFORMANCE_HPP

/*
#include <srs_core_performance.hpp>
*/

#include <srs_core.hpp>

/**
* this file defines the perfromance options.
*/

/**
* to improve read performance, merge some packets then read,
* when it on and read small bytes, we sleep to wait more data.,
* that is, we merge some data to read together.
* @see SrsConfig::get_mr_enabled()
* @see SrsConfig::get_mr_sleep_ms()
* @see https://github.com/winlinvip/simple-rtmp-server/issues/241
* @example, for the default settings, this algorithm will use:
*       that is, when got nread bytes smaller than 4KB, sleep(780ms).
*/
/**
* https://github.com/winlinvip/simple-rtmp-server/issues/241#issuecomment-65554690
* The merged read algorithm is ok and can be simplified for:
*   1. Suppose the client network is ok. All algorithm go wrong when netowrk is not ok.
*   2. Suppose the client send each packet one by one. Although send some together, it's same.
*   3. SRS MR algorithm will read all data then sleep.
* So, the MR algorithm is:
*   while true:
*       read all data from socket.
*       sleep a while
* For example, sleep 120ms. Then there is, and always 120ms data in buffer.
* That is, the latency is 120ms(the sleep time).
*/
#define SRS_PERF_MERGED_READ
// the default config of mr.
#define SRS_PERF_MR_ENABLED false
#define SRS_PERF_MR_SLEEP 500

/**
* the MW(merged-write) send cache time in ms.
* the default value, user can override it in config.
* to improve send performance, cache msgs and send in a time.
* for example, cache 500ms videos and audios, then convert all these
* msgs to iovecs, finally use writev to send.
* @remark this largely improve performance, from 3.5k+ to 7.5k+.
*       the latency+ when cache+.
* @remark the socket send buffer default to 185KB, it large enough.
* @see https://github.com/winlinvip/simple-rtmp-server/issues/194
* @see SrsConfig::get_mw_sleep_ms()
*/
// the default config of mw.
#define SRS_PERF_MW_SLEEP 500

/**
* how many chunk stream to cache, [0, N].
* to imporove about 10% performance when chunk size small, and 5% for large chunk.
* @see https://github.com/winlinvip/simple-rtmp-server/issues/249
* @remark 0 to disable the chunk stream cache.
*/
#define SRS_PERF_CHUNK_STREAM_CACHE 16

/**
* the gop cache and play cache queue.
*/
// whether gop cache is on.
#define SRS_PERF_GOP_CACHE true
// in seconds, the live queue length.
#define SRS_PERF_PLAY_QUEUE 30

#endif

