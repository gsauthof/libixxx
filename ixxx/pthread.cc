// Copyright (c) 2014, Georg Sauthoff <mail@georg.so>

// SPDX-License-Identifier: BSD-2-Clause

#include "pthread.hh"
#include "sys_error.hh"


namespace ixxx {

    namespace posix {

        void pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                void *(*start_routine) (void *), void *arg)
        {
            int r = ::pthread_create(thread, attr, start_routine, arg);
            if (r)
                throw pthread_create_error(r);
        }
        void pthread_join(pthread_t thread, void **retval)
        {
            int r = ::pthread_join(thread, retval);
            if (r)
                throw pthread_join_error(r);
        }

        void pthread_attr_init(pthread_attr_t *attr)
        {
            int r = ::pthread_attr_init(attr);
            if (r)
                throw pthread_attr_init_error(r);
        }
        void pthread_attr_destroy(pthread_attr_t *attr)
        {
            int r = ::pthread_attr_destroy(attr);
            if (r)
                throw pthread_attr_destroy_error(r);
        }

        void pthread_attr_setaffinity_np(pthread_attr_t *attr,
                size_t cpusetsize, const cpu_set_t *cpuset)
        {
            int r = ::pthread_attr_setaffinity_np(attr, cpusetsize, cpuset);
            if (r)
                throw pthread_attr_setaffinity_np_error(r);
        }
        void pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy)
        {
            int r = ::pthread_attr_setschedpolicy(attr, policy);
            if (r)
                throw pthread_attr_setschedpolicy_error(r);
        }
        void pthread_attr_setschedparam(pthread_attr_t *attr,
                const struct sched_param *param)
        {
            int r = ::pthread_attr_setschedparam(attr, param);
            if (r)
                throw pthread_attr_setschedparam_error(r);
        }
        void pthread_attr_setinheritsched(pthread_attr_t *attr,
                int inheritsched)
        {
            int r = ::pthread_attr_setinheritsched(attr, inheritsched);
            if (r)
                throw pthread_attr_setinheritsched_error(r);
        }


    }

}
