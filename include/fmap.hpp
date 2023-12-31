#pragma once

#include <concepts>

#ifndef FMAP_HPP
#define FMAp_HPP

template <class A_B, class FA, class FB> struct fmap {
    FB operator()(A_B, FA &);
};

#endif
