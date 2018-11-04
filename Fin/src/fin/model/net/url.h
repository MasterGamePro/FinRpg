#pragma once

#include <string>

namespace fin::net {
  class Url {
    public:
    static Url from_url(std::string) {
      
    }

    std::string get_scheme() const { return scheme_; }
    std::string get_authority() const { return authority_; }
    std::string get_user_info() const { return user_info_; }
    std::string get_host() const { return host_; }
    std::string get_port() const { return port_; }
    std::string get_path() const { return path_; }
    std::string get_query() const { return query_; }
    std::string get_fragment() const { return fragment_; }

    explicit operator bool() const { return is_valid_; }

    private:
    Url(const std::string& scheme, const std::string& user_info,
        const std::string& host, const std::string& port,
        const std::string& path, const std::string& query,
        const std::string& fragment, const bool is_valid) : scheme_(scheme),
                                                            authority_(),
                                                            user_info_(user_info),
                                                            host_(host),
                                                            port_(port),
                                                            path_(path),
                                                            query_(query),
                                                            fragment_(fragment),
                                                            is_valid_(is_valid) {
    }

    std::string scheme_;
    std::string authority_;
    std::string user_info_;
    std::string host_;
    std::string port_;
    std::string path_;
    std::string query_;
    std::string fragment_;
    bool is_valid_;
  };
}
