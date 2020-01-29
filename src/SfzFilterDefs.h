#pragma once

enum {
    /**
       Minimum interval in frames between recomputations of coefficients of the
       modulated filter. The lower, the more CPU resources are consumed.
    */
    kSfzFilterControlInterval = 16,
};
