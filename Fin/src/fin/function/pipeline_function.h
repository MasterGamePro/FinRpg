#pragma once

namespace fin::function {
  template <typename INPUT_TYPE, typename RETURN_TYPE>
  class IPipelineFunction {
    public:
    RETURN_TYPE operator()(INPUT_TYPE param) {
      return 
    }

    RETURN_TYPE then(INPUT_TYPE) {
      return 
    }

    private:
    std::function<RETURN_TYPE(INPUT_TYPE)> lambda;
    IPipelineFunction<> next;
  };
}