#include <array>

#ifndef NOTES_HPP
#define NOTES_HPP

const float noteA4 = 440.0;
const float noteBb4 = 466.2;
const float noteB4 = 493.9;
const float noteC5 = 523.3;
const float noteDb5 = 554.4;
const float noteD5 = 587.3;
const float noteEb5 = 622.3;
const float noteE5 = 659.3;
const float noteF5 = 698.5;
const float noteGb5 = 740.0;
const float noteG5 = 784.0;
const float noteAb5 = 830.6;

const float noteA8 = noteA4 * 16;
const float noteA7 = noteA4 * 8;
const float noteA6 = noteA4 * 4;
const float noteA5 = noteA4 * 2;
const float noteA3 = noteA4 / 2;
const float noteA2 = noteA4 / 4;
const float noteA1 = noteA4 / 8;
const float noteA0 = noteA4 / 16;

const float noteBb8 = noteBb4 * 16;
const float noteBb7 = noteBb4 * 8;
const float noteBb6 = noteBb4 * 4;
const float noteBb5 = noteBb4 * 2;
const float noteBb3 = noteBb4 / 2;
const float noteBb2 = noteBb4 / 4;
const float noteBb1 = noteBb4 / 8;
const float noteBb0 = noteBb4 / 16;

const float noteB8 = noteB4 * 16;
const float noteB7 = noteB4 * 8;
const float noteB6 = noteB4 * 4;
const float noteB5 = noteB4 * 2;
const float noteB3 = noteB4 / 2;
const float noteB2 = noteB4 / 4;
const float noteB1 = noteB4 / 8;
const float noteB0 = noteB4 / 16;

const float noteC8 = noteC5 * 8;
const float noteC7 = noteC5 * 4;
const float noteC6 = noteC5 * 2;
const float noteC4 = noteC5 / 2;
const float noteC3 = noteC5 / 4;
const float noteC2 = noteC5 / 8;
const float noteC1 = noteC5 / 16;
const float noteC0 = noteC5 / 32;

const float noteDb8 = noteDb5 * 8;
const float noteDb7 = noteDb5 * 4;
const float noteDb6 = noteDb5 * 2;
const float noteDb4 = noteDb5 / 2;
const float noteDb3 = noteDb5 / 4;
const float noteDb2 = noteDb5 / 8;
const float noteDb1 = noteDb5 / 16;
const float noteDb0 = noteDb5 / 32;

const float noteD8 = noteD5 * 8;
const float noteD7 = noteD5 * 4;
const float noteD6 = noteD5 * 2;
const float noteD4 = noteD5 / 2;
const float noteD3 = noteD5 / 4;
const float noteD2 = noteD5 / 8;
const float noteD1 = noteD5 / 16;
const float noteD0 = noteD5 / 32;

const float noteEb8 = noteEb5 * 8;
const float noteEb7 = noteEb5 * 4;
const float noteEb6 = noteEb5 * 2;
const float noteEb4 = noteEb5 / 2;
const float noteEb3 = noteEb5 / 4;
const float noteEb2 = noteEb5 / 8;
const float noteEb1 = noteEb5 / 16;
const float noteEb0 = noteEb5 / 32;

const float noteE8 = noteE5 * 8;
const float noteE7 = noteE5 * 4;
const float noteE6 = noteE5 * 2;
const float noteE4 = noteE5 / 2;
const float noteE3 = noteE5 / 4;
const float noteE2 = noteE5 / 8;
const float noteE1 = noteE5 / 16;
const float noteE0 = noteE5 / 32;

const float noteF8 = noteF5 * 8;
const float noteF7 = noteF5 * 4;
const float noteF6 = noteF5 * 2;
const float noteF4 = noteF5 / 2;
const float noteF3 = noteF5 / 4;
const float noteF2 = noteF5 / 8;
const float noteF1 = noteF5 / 16;
const float noteF0 = noteF5 / 32;

const float noteGb8 = noteGb5 * 8;
const float noteGb7 = noteGb5 * 4;
const float noteGb6 = noteGb5 * 2;
const float noteGb4 = noteGb5 / 2;
const float noteGb3 = noteGb5 / 4;
const float noteGb2 = noteGb5 / 8;
const float noteGb1 = noteGb5 / 16;
const float noteGb0 = noteGb5 / 32;

const float noteG8 = noteG5 * 8;
const float noteG7 = noteG5 * 4;
const float noteG6 = noteG5 * 2;
const float noteG4 = noteG5 / 2;
const float noteG3 = noteG5 / 4;
const float noteG2 = noteG5 / 8;
const float noteG1 = noteG5 / 16;
const float noteG0 = noteG5 / 32;

const float noteAb8 = noteAb5 * 8;
const float noteAb7 = noteAb5 * 4;
const float noteAb6 = noteAb5 * 2;
const float noteAb4 = noteAb5 / 2;
const float noteAb3 = noteAb5 / 4;
const float noteAb2 = noteAb5 / 8;
const float noteAb1 = noteAb5 / 16;
const float noteAb0 = noteAb5 / 32;

const std::array<float, 108> noteArray = {noteC0, noteDb0, noteD0, noteEb0, noteE0, noteF0, noteGb0, noteG0, noteAb0, noteA0, noteBb0, noteB0,
        noteC1, noteDb1, noteD1, noteEb1, noteE1, noteF1, noteGb1, noteG1, noteAb1, noteA1, noteBb1, noteB1,
        noteC2, noteDb2, noteD2, noteEb2, noteE2, noteF2, noteGb2, noteG2, noteAb2, noteA2, noteBb2, noteB2,
        noteC3, noteDb3, noteD3, noteEb3, noteE3, noteF3, noteGb3, noteG3, noteAb3, noteA3, noteBb3, noteB3,
        noteC4, noteDb4, noteD4, noteEb4, noteE4, noteF4, noteGb4, noteG4, noteAb4, noteA4, noteBb4, noteB4,
        noteC5, noteDb5, noteD5, noteEb5, noteE5, noteF5, noteGb5, noteG5, noteAb5, noteA5, noteBb5, noteB5,
        noteC6, noteDb6, noteD6, noteEb6, noteE6, noteF6, noteGb6, noteG6, noteAb6, noteA6, noteBb6, noteB6,
        noteC7, noteDb7, noteD7, noteEb7, noteE7, noteF7, noteGb7, noteG7, noteAb7, noteA7, noteBb7, noteB7,
        noteC8, noteDb8, noteD8, noteEb8, noteE8, noteF8, noteGb8, noteG8, noteAb8, noteA8, noteBb8, noteB8};

#endif /* NOTES_HPP */
