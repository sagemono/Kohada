#pragma once

#include <QString>
#include <QMap>
#include <cstdint>

namespace syscon {

struct ErrorCodeInfo {
    QString short_name;     // e.g. "CELL_POWER_FAIL"
    QString description;    // human readable
    QString component;      // CELL, RSX, SB, PSU, etc.
    QString severity_hint;  // info, warning, error, fatal
    QString community_note; // repair context
};

inline uint8_t error_prefix(uint32_t code)    { return (code >> 24) & 0xFF; }
inline uint8_t error_phase(uint32_t code)     { return (code >> 16) & 0xFF; }
inline uint16_t error_subcode(uint32_t code)  { return code & 0xFFFF; }

inline QString format_error_code(uint32_t code) {
    return QString("0x%1").arg(code, 8, 16, QChar('0'));
}

inline QString phase_name(uint8_t phase) {
    switch (phase) {
        case 0x80: return "PowerSeq";
        case 0x40: return "BitTraining";
        case 0xA0: return "RSX Init";
        case 0x20: return "SB Init";
        case 0x90: return "Thermal";
        case 0x23: return "SB Config";
        default:
            return QString("Phase 0x%1").arg(phase, 2, 16, QChar('0'));
    }
}

inline ErrorCodeInfo error_code_info(uint32_t code) {
    static const QMap<uint32_t, ErrorCodeInfo> known_codes = {
        {0xA0801001, {
            "CELL_POWER_FAIL", "CELL Vcore power failure",
            "CELL / NEC-TOKIN", "fatal",
            "To be added"
            "To be added"
        }},
        {0xA0801002, {
            "CELL_POWER_TIMEOUT", "CELL power-on sequence timeout",
            "CELL / VRM", "fatal",
            "To be added"
            "To be added"
            "To be added"
        }},
        {0xA08014FF, {
            "POWSEQ_ABNORMAL_END", "Power sequence abnormal termination",
            "Power", "fatal",
            "To be added"
            "To be added"
        }},
        {0xA0801701, {
            "POWSEQ_VRM_FAIL", "Power sequence VRM failure",
            "VRM", "fatal",
            "To be added"
            "To be added"
        }},
        {0xA0801003, {
            "RSX_POWER_FAIL", "RSX Vcore power failure",
            "RSX / VRM", "fatal",
            "To be added"
        }},

        {0xA0403034, {
            "RSX_BITTRAINING", "RSX BitTraining FlexIO error",
            "RSX / BGA", "fatal",
            "To be added"
        }},
        {0xA0404002, {
            "BITTRAINING_ID_FAIL", "BitTraining FlexIO ID mismatch",
            "RSX / FlexIO", "fatal",
            "To be added"
        }},

        {0xA0A02031, {
            "RSX_INIT_FAIL", "RSX initialization failure",
            "RSX", "fatal",
            "To be added"
        }},

        {0xA0201B02, {
            "SB_INIT_FAIL", "Southbridge initialization failure",
            "Southbridge", "fatal",
            "To be added"
        }},

        {0xA0232102, {
            "SB_CONFIG_FAIL", "Southbridge configuration error",
            "Southbridge", "fatal",
            "To be added"
            "To be added"
        }},

        {0xA0902120, {
            "THERMAL_SHUTDOWN", "Thermal shutdown triggered",
            "Thermal", "error",
            "To be added"
            "To be added"
        }},
        {0xA0902121, {
            "THERMAL_ALERT", "Thermal alert threshold exceeded",
            "Thermal", "warning",
            "To be added"
            "To be added"
        }},
    };

    auto it = known_codes.find(code);
    if (it != known_codes.end()) {
        return it.value();
    }

    uint8_t phase = error_phase(code);
    uint16_t sub = error_subcode(code);

    ErrorCodeInfo generic;
    generic.component = phase_name(phase);
    generic.severity_hint = "unknown";
    generic.short_name = QString("ERR_%1_%2")
        .arg(phase, 2, 16, QChar('0'))
        .arg(sub, 4, 16, QChar('0'));
    generic.description = QString("%1 error (code: 0x%2)")
        .arg(phase_name(phase))
        .arg(sub, 4, 16, QChar('0'));
    generic.community_note = "Unknown error code. Please report to the community.";

    return generic;
}

inline QString error_code_description(uint32_t code) {
    auto info = error_code_info(code);
    return info.description;
}

} // namespace syscon