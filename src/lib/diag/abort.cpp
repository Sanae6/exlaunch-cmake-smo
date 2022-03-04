/*
 * Copyright (c) Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "abort.hpp"

#include <algorithm>
#include <atomic>
#include <cstring>

namespace exl::diag {

    void NORETURN NOINLINE AbortImpl(const AbortCtx& ctx) {
        {
            svcBreak(ctx.m_Result, 0, 0);
        }

        UNREACHABLE;
    }

#define ABORT_WITH_VALUE(v)                                                                                            \
    {                                                                                                                  \
        exl::diag::AbortCtx ctx{.m_Result = (Result)v};                                                                \
        AbortImpl(ctx);                                                                                                \
    }

    /* TODO: better assert/abort support. */
    void NORETURN NOINLINE AssertionFailureImpl(const char* file, int line, const char* func, const char* expr,
                                                u64 value, const char* format, ...)
        ABORT_WITH_VALUE(value) void NORETURN NOINLINE
        AssertionFailureImpl(const char* file, int line, const char* func, const char* expr, u64 value)
            ABORT_WITH_VALUE(value) void NORETURN NOINLINE
        AbortImpl(const char* file, int line, const char* func, const char* expr, u64 value, const char* format, ...)
            ABORT_WITH_VALUE(value) void NORETURN NOINLINE
        AbortImpl(const char* file, int line, const char* func, const char* expr, u64 value) ABORT_WITH_VALUE(value)

}; // namespace exl::diag

/* C shim for libnx */
extern "C" NORETURN void exl_abort(Result r) ABORT_WITH_VALUE(r)