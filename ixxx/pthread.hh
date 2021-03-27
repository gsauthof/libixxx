// Copyright (c) 2014, Georg Sauthoff <mail@georg.so>

// SPDX-License-Identifier: BSD-2-Clause

#ifndef IXXX_PTHREAD_HH
#define IXXX_PTHREAD_HH


#include <pthread.h>

namespace ixxx {

    namespace posix {

        void pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                void *(*start_routine) (void *), void *arg);
        void pthread_join(pthread_t thread, void **retval);

        void pthread_attr_init(pthread_attr_t *attr);
        void pthread_attr_destroy(pthread_attr_t *attr);

        void pthread_attr_setaffinity_np(pthread_attr_t *attr,
                size_t cpusetsize, const cpu_set_t *cpuset);
        void pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy);
        void pthread_attr_setschedparam(pthread_attr_t *attr,
                const struct sched_param *param);
        void pthread_attr_setinheritsched(pthread_attr_t *attr,
                int inheritsched);


    }

}

#endif
