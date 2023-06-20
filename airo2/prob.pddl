(define (problem prob1)
(:domain localization)
(:objects
     a1 a2 a3 a4 - assignment
     r0 r1 r2 r3 r4 r5 r6 r7 r8 r9 r10 r11 r12 r13 r14 r15 r16 r17 r18 r19 r20 r21 r22 r23 r24 r25 r26 r27 r28 r29 - region
     R2D2 - robot
)
(:init
    (robot_in R2D2 r0)

    (= (act-cost) 0)
    (= (dummy) 0)

    (is_in a1 r1) (is_in a2 r2) (is_in a3 r3) (is_in a4 r4)
 )

(:goal 
     (and (visited r1))
)

     (:metric minimize (act-cost))
)
