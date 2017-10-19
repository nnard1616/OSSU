;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname practice_HtDF) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define L1 (cons "Apple" (cons "Banana" (cons "Orange" (cons "Pear" empty)))))

(first (rest (rest L1)))
(define fuck (cons "end" empty))
(first fuck)