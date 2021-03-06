#pragma once

#include "telnetpp/server_option.hpp"
#include <boost/optional.hpp>
#include <utility>

namespace telnetpp { namespace options { namespace naws {

//* =========================================================================
/// \brief An implementation of the server side of the Telnet NAWS option.
//* =========================================================================
class TELNETPP_EXPORT server : public telnetpp::server_option {
public :
    //* =====================================================================
    /// CONSTRUCTOR
    //* =====================================================================
    server();

    //* =====================================================================
    /// \brief Sets the window size that this option will report.
    //* =====================================================================
    std::vector<telnetpp::token> set_window_size(u16 width, u16 height);

private :
    //* =====================================================================
    /// \brief Handle a negotiation that has been received in the active
    /// state.
    //* =====================================================================
    std::vector<telnetpp::token> handle_subnegotiation(
        u8stream const &content) override;

    //* =====================================================================
    /// \brief Report the window size.
    //* =====================================================================
    std::vector<telnetpp::token> report_window_size();

    boost::optional<std::pair<telnetpp::u16, telnetpp::u16>> window_size_;
};

}}}
