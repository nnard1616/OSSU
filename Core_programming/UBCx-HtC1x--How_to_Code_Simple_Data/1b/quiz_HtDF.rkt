;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname quiz_HtDF) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/image)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Prototypes
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Image, Image -> boolean
; Compares two images (rectangles), returns true if first image is larger
; than the second, else false.
; larger: means it has a larger area, width*height

;(define (is_larger? img1 img2) false)

; Image -> Number
; Returns width*height of an image

;(define (area img) 0)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Constants
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define rect1 (rectangle 22 2 "outline" "black"))
(define rect2 (rectangle 22 22 "outline" "black"))
(define rect3 (rectangle 2 22 "outline" "black"))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Tests
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; tests for area
(check-expect (area rect1) 44)
(check-expect (area rect2) 484)
(check-expect (area rect3) 44)

; tests for is_larger
(check-expect (is_larger? rect1 rect2) false) ;smaller area
(check-expect (is_larger? rect2 rect3) true)  ;larger area
(check-expect (is_larger? rect1 rect3) false) ;equal area


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Pseudocode
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;(define (is_larger? img1 img2)     ;take two rectangles
;  (... first_area second_area) )   ;if first area is larger than second:
                                    ;   return true
                                    ;else: return false

; Return Image Width * Image Height, the area.
;(define (area img) (... img_width img_height))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Implementations
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (is_larger? img1 img2)      ;take two rectangles
  (> (area img1) (area img2)) )     ;if first area is larger than second:
                                    ;   return true
                                    ;else: return false
 
; Return Image Width * Image Height, the area.
(define (area img) (* (image-width img) (image-height img)))