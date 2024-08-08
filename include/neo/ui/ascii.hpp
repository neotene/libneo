#ifndef NEO_UI_ASCII
#define NEO_UI_ASCII

#include <cstdlib>
#include <map>
#include <string>
#include <iostream>

namespace neo {
namespace ui {

enum class ascii
{
    /*
     * Made by Nathan Kolpa
     */

    // control characters

    _null,   // NULL
    soh,     // Start of Heading
    stx,     // Start of Text
    etx,     // End of Text
    eot,     // End of Transmission
    enq,     // Enquiry
    ack,     // Acknowledgement
    bel,     // Bell
    bs,      // Backspace
    tab,     // Horizontal Tab
    lf,      // Line Feed
    vt,      // Vertical Tab
    ff,      // Form Feed
    cr,      // Carriage Return
    so,      // Shift Out
    si,      // Shift In
    dle,     // Data Link Escape
    dc1,     // Device Control 1
    dc2,     // Device Control 2
    dc3,     // Device Control 3
    dc4,     // Device Control 4
    nak,     // Negative Acknowledgement
    syn,     // Synchronous Idle
    etb,     // End of Transmission Block
    can,     // Cancel
    em,      // End of Medium
    sub,     // Substitute
    esc,     // Escape
    sf,      // File Separator
    gs,      // Group Separator
    rs,      // Record Separator
    us,      // Unit Separator

    // misc characters

    space,                   // space
    exclamaion_mark,         // !
    quotation_mark_double,   // "
    hashtag,                 // #
    sing_dollar,             // $
    precent,                 // %
    ampersant,               // &
    quotation_mark_single,   // '
    parentheses_open,        // (
    parentheses_close,       // )
    asterisk,                // *
    plus,                    // +
    comma,                   // ,
    minus,                   // -
    dot,                     // .
    slash_foward,            // /
    number_0,                // 0
    number_1,                // 1
    number_2,                // 2
    number_3,                // 3
    number_4,                // 4
    number_5,                // 5
    number_6,                // 6
    number_7,                // 7
    number_8,                // 8
    number_9,                // 9
    colon,                   // :
    colon_semi,              // ;
    less_than,               // <
    equal_to,                // =
    greater_than,            // >
    question_mark,           // ?
    sing_at,                 // @

    // upper case alphabet

    a_upper,   // A
    b_upper,   // B
    c_upper,   // C
    d_upper,   // D
    e_upper,   // E
    f_upper,   // F
    g_upper,   // G
    h_upper,   // H
    i_upper,   // I
    j_upper,   // J
    k_upper,   // K
    l_upper,   // L
    m_upper,   // M
    n_upper,   // N
    o_upper,   // O
    p_upper,   // P
    q_upper,   // Q
    r_upper,   // R
    s_upper,   // S
    t_upper,   // T
    u_upper,   // U
    v_upper,   // V
    w_upper,   // W
    x_upper,   // X
    y_upper,   // Y
    z_upper,   // Z

    // misc characters

    bracket_open,     // [
    slash_backward,   //
    bracket_close,    // ]
    caret,            // ^
    underscore,       // _
    grave_accent,     // `

    // lower case alphabet

    a_lower,   // a
    b_lower,   // b
    c_lower,   // c
    d_lower,   // d
    e_lower,   // e
    f_lower,   // f
    g_lower,   // g
    h_lower,   // h
    i_lower,   // i
    j_lower,   // j
    k_lower,   // k
    l_lower,   // l
    m_lower,   // m
    n_lower,   // n
    o_lower,   // o
    p_lower,   // p
    q_lower,   // q
    r_lower,   // r
    s_lower,   // s
    t_lower,   // t
    u_lower,   // u
    v_lower,   // v
    w_lower,   // w
    x_lower,   // x
    y_lower,   // y
    z_lower,   // z

    // misc characters

    bracket_curly_open,    // {
    vertical_bar,          // |
    bracket_curly_close,   // }
    tilde,                 // ~

    del,   // Delete

    //===================[extended ascii]===================

    // misc letters

    c_upper_cedilla,   // Ç

    u_lower_umlaut,       // ü
    e_lower_acute,        // é
    a_lower_circumflex,   // â
    a_lower_umlaut,       // ä
    a_lower_grave,        // à
    a_lower_ring,         // å
    c_lower_cedilla,      // ç
    e_lower_circumflex,   // ê
    e_lower_umlaut,       // ë
    e_lower_grave,        // è
    i_lower_umlaut,       // ï
    i_lower_circumflex,   // î
    i_lower_grave,        // ì
    a_upper_umlaut,       // Ä
    a_upper_ring,         // Å
    e_upper_acute,        // É
    ae_lower,             // æ
    ae_upper,             // Æ
    o_lower_circumflex,   // ô
    o_lower_umlaut,       // ö
    o_lower_grave,        // ò
    u_lower_circumflex,   // û
    u_lower_grave,        // ù
    y_lower_umlaut,       // ÿ
    o_upper_umlaut,       // Ö
    u_upper_umlaut,       // Ü

    sing_cent,      // ¢
    sing_pound,     // £
    sing_yen,       // ¥
    sing_pesta,     // ₧
    f_lower_hook,   // ƒ

    a_lower_acute,   // á
    i_lower_acute,   // í
    o_lower_acute,   // ó
    u_lower_acute,   // ú
    n_lower_tilde,   // ñ
    n_upper_tilde,   // Ñ

    // symbols

    ordinal_indicator_feminine,          // ª
    ordinal_indicator_masculine,         // º
    question_mark_reversed,              // ¿
    sing_not_reversed,                   // ⌐
    sing_not,                            // ¬
    vulgar_fraction_half,                // ½
    vulgar_fraction_quarter,             // ¼
    exclamation_mark_inverted,           // ¡
    quotation_mark_double_angle_left,    // «
    quotation_mark_double_angle_right,   // »

    /* box drawings
     * box_[direction1]_[thickness]_[direction2]_[thickness]
     * if you cant find a combination try switching the direction combination
     */

    shade_light,    // ░
    shade_medium,   // ▒
    shade_dark,     // ▓

    box_vertical_light,                      // │
    box_vertical_light_left_light,           // ┤
    box_vertical_single_left_double,         // ╡
    box_vertical_double_left_single,         // ╢
    box_down_double_left_single,             // ╖
    box_down_single_left_double,             // ╕
    box_vertical_double_left_double,         // ╣
    box_vertical_double,                     // ║
    box_down_double_left_double,             // ╗
    box_up_double_left_double,               // ╝
    box_up_double_left_single,               // ╜
    box_up_single_left_double,               // ╛
    box_down_light_left_light,               // ┐
    box_up_light_right_light,                // └
    box_up_light_horizontal_light,           // ┴
    box_down_light_horizontal_light,         // ┬
    box_vertical_light_right_light,          // ├
    box_horizontal_light,                    // ─
    box_vertical_light_horizontal_light,     // ┼
    box_vertical_single_right_double,        // ╞
    box_vertical_double_right_single,        // ╟
    box_up_double_right_double,              // ╚
    box_down_double_right_double,            // ╔
    box_up_double_horizontal_double,         // ╩
    box_down_double_horizontal_double,       // ╦
    box_vertical_double_right_double,        // ╠
    box_horizontal_double,                   // ═
    box_vertical_double_horizontal_double,   // ╬
    box_up_single_horizontal_double,         // ╧
    box_up_double_horizontal_single,         // ╨
    box_down_single_horizontal_double,       // ╤
    box_down_double_horizontal_single,       // ╥
    box_up_double_right_single,              // ╙
    box_up_single_right_single,              // ╘
    box_down_single_right_double,            // ╒
    box_down_single_right_single,            // ╓
    box_vetrical_double_horizontal_single,   // ╫
    box_vertical_single_horizontaldouble,    // ╪
    box_up_light_left_light,                 // ┘
    box_down_light_right_light,              // ┌

    block_full,         // █
    block_half_lower,   // ▄
    block_half_left,    // ▌
    block_half_right,   // ▐
    block_half_upper,   // ▀

    // other letters

    aplha_lower,     // α
    s_sharp_lower,   // ß
    gamma_upper,     // Γ
    pi_lower,        // π
    sigma_upper,     // Σ
    sigma_lower,     // σ

    sing_micro,                 // µ
    tau_lower,                  // τ
    phi_upper,                  // Φ
    theta_upper,                // Θ
    omega_upper,                // Ω
    delta_lower,                // δ
    infinite,                   // ∞
    phi_lower,                  // φ
    epsilon_lower,              // ε
    intersection,               // ∩
    identical_to,               // ≡
    sing_plus_minus,            // ±
    greater_than_or_equal_to,   // ≥
    less_than_or_equal_to,      // ≤
    half_integral_top,          // ⌠
    half_integral_bottom,       // ⌡
    sing_division,              // ÷
    equal_to_almost,            // ≈
    sing_degree,                // °
    buller_operator,            // ∙
    dot_middle,                 // ·
    square_root,                // √
    n_superscript_lower,        // ⁿ
    number_2_superscript,       // ²
    black_square,               // ■
    space_no_break,             //
};

enum class term_char
{
    vertical,
    horizontal,
    left_up_corner,
    right_up_corner,
    left_down_corner,
    right_down_corner,
};

using vt100_char = decltype(u'│');

extern std::map<term_char, vt100_char> vt100_term_chars;
extern std::map<term_char, wchar_t> basic_term_chars;

vt100_char
get_character(term_char const &tc)
{
    constexpr char expected[] = "xterm-256color";

    char *current_term = std::getenv("TERM");

    if (current_term != nullptr && std::string(current_term) == expected) {
        return vt100_term_chars[tc];
    }
    else {
        return static_cast<vt100_char>(basic_term_chars[tc]);
    }
}

template <class CHAR>
void
ascii_to(CHAR &chr, ascii ascii_char)
{
    chr = static_cast<CHAR>(ascii_char);
}

}   // namespace ui
}   // namespace neo

#endif
