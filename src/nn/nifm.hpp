#pragma once

#include "nn_common.hpp"

namespace nn {
    namespace nifm {

        Result Initialize();
        void SubmitNetworkRequest();
        void SubmitNetworkRequestAndWait();
        void CancelNetworkRequest();
        bool IsNetworkRequestOnHold();
        bool IsNetworkAvailable();

    }
}
