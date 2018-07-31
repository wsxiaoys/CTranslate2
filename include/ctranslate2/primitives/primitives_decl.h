#pragma once

#include "ctranslate2/devices.h"

namespace ctranslate2 {

  template <Device D = Device::CPU>
  struct primitives {

    static void* alloc_data(size_t size);
    static void free_data(void* data);

    template <typename T>
    static void fill(T* x, T a, size_t size);

    template <typename T>
    static void copy(const T* x, T* y, size_t size);

    template <typename T>
    static T sum(const T* array, size_t size);

    template <typename T>
    static T mean(const T* array, size_t size) {
      return sum(array, size) / size;
    }

    template <typename T>
    static size_t max_element(const T* array, size_t size);

    template <typename T>
    static T max(const T* array, size_t size);

    template <typename T, typename I>
    static void topk(const T* x, T* values, I* indices, size_t k, size_t size);

    template <typename T>
    static void add(T a, const T* x, T* y, size_t size);

    template <typename T>
    static void add(T a, T* y, size_t size) {
      add(a, y, y, size);
    }

    template <typename T>
    static void add(const T* a, const T* b, T* c, size_t size);

    template <typename T>
    static void add(const T* x, T* y, size_t size) {
      add(x, y, y, size);
    }

    template <typename T>
    static void add_batch_broadcast(const T* a, const T* b, T* c, size_t a_size, size_t b_size);

    template <typename T>
    static void add_batch_broadcast(const T* x, T* y, size_t x_size, size_t y_size) {
      add_batch_broadcast(x, y, y, x_size, y_size);
    }

    template <typename T>
    static void sub(T a, const T* x, T* y, size_t size) {
      T a_rev = -a;
      add(a_rev, x, y, size);
    }

    template <typename T>
    static void sub(T a, T* y, size_t size) {
      sub(a, y, y, size);
    }

    template <typename T>
    static void sub(const T* a, const T* b, T* c, size_t size);

    template <typename T>
    static void mul(T a, const T* x, T* y, size_t size);

    template <typename T>
    static void mul(T a, T* y, size_t size) {
      mul(a, y, y, size);
    }

    template <typename T>
    static void mul(const T* a, const T* b, T* c, size_t size);

    template <typename T>
    static void mul(const T* x, T* y, size_t size) {
      mul(x, y, y, size);
    }

    template <typename T>
    static void inv(const T* x, T* y, size_t size);

    template <typename In, typename Out>
    static void quantize(const In* x, Out* y, size_t size, In scale, In shift);

    template <typename In, typename Out>
    static void unquantize(const In* x, Out* y, size_t size, Out scale, Out shift);

    template <typename T>
    static void relu(const T* x, T* y, size_t size);

    template <typename T>
    static void relu(T* x, size_t size) {
      relu(x, x, size);
    }

    template <typename DataType, typename IndexType>
    static void transpose_2d(const DataType* a, const IndexType* dims, DataType* b);

    template <typename DataType, typename IndexType>
    static void transpose_3d(const DataType* a,
                             const IndexType* dims,
                             const IndexType* perm,
                             DataType* b);

    template <typename DataType, typename IndexType>
    static void transpose_4d(const DataType* a,
                             const IndexType* dims,
                             const IndexType* perm,
                             DataType* b);

    template <typename T>
    static void pow(const T* x, T* y, T power, size_t size);

    template <typename T>
    static void exp(const T* x, T* y, size_t size);

    template <typename T>
    static void cos(const T* x, T* y, size_t size);

    template <typename T>
    static void sin(const T* x, T* y, size_t size);

    template <typename T>
    static void tanh(const T* x, T* y, size_t size);

    template <typename In, typename Out>
    static void gemm(const In* a, const In* b,
                     bool transpose_a, bool transpose_b,
                     size_t m, size_t n, size_t k,
                     In alpha, Out beta,
                     Out* c);

    template <typename In, typename Out>
    static void gemm_batch(const In* a, const In* b,
                           bool transpose_a, bool transpose_b,
                           size_t batch_size,
                           size_t m, size_t n, size_t k,
                           In alpha, Out beta,
                           Out* c) {
      for (size_t i = 0; i < batch_size; ++i) {
        const In* a_i = a + (i * m * k);
        const In* b_i = b + (i * k * n);
        Out* c_i = c + (i * m * n);

        gemm(a_i, b_i, transpose_a, transpose_b, m, n, k, alpha, beta, c_i);
      }
    }
  };

  template <Device D1, Device D2>
  struct cross_device_primitives {
    template <typename T>
    static void copy(const T* x, T* y, size_t size);
  };

}
