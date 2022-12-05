---
title: 'Pinocchio - Nearly Practical Verifiable Computation'
author:
    'Advai Swamy- 106119006, Dipesh Kafle - 106119029 and Harsh Khandelwal -
    106119048'
institute: 'National Institute of Technology, Tiruchirappalli'
topic: 'Paper Presentation'
theme: 'Frankfurt'
colortheme: 'beaver'
fonttheme: 'professionalfonts'
fontsize: 10pt
lang: en-US
section-titles: true
colorlinks: true
linkcolor: blue
urlcolor: red
header-includes: |
    \usepackage{fancyhdr}
    \pagestyle{fancy}
    \usepackage{graphicx}
    \usepackage{amsfonts} 
    \usepackage{amssymb}
    \usepackage{amsmath}
---

## Introduction

What is verified computing?

-   Since computational power is often asymmetric (particularly for mobile
    devices), a relatively weak client may wish to outsource computation to one
    or more powerful workers
-   In all of these settings, the client should be able to verify the results
    returned, to guard against malicious or malfunctioning workers
-   Most of VC work has either been function specific, relied on assumptions we
    prefer to avoid, or simply failed to pass basic practicality requirements.
-   Pinocchio is a concrete system for efficiently verifying general
    computations while making only cryptographic assumptions. It supports even
    Public Verifiable Computation ,which allows an untrusted worker to produce
    signatures of computation.

## Introduction (continued)

-   Pinocchio’s asymptotics are excellent: key setup and proof generation
    require cryptographic effort linear in the size of the original computation,
    and verification requires time linear in the size of the inputs and outputs.
-   To achieve efficient verifiable computation, Pinocchio combines quadratic
    programs, a computational model introduced by Gennaro et al. , with a series
    of theoretical refinements and systems engineering to produce an end-to-end
    toolchain for verifying computations.

## Homormophic Hiding

An HH E(x) of a number x is a function satisfying the following properties:

-   For most x’s, given E(x) it is hard to find x.
-   Different inputs lead to different outputs – so if $x≠y$, then $E(x)≠E(y)$.
-   If someone knows E(x) and E(y), they can generate the HH of arithmetic
    expressions in x and y. For example, they can compute E(x+y) from E(x) and
    E(y).

## Homormophic Hiding Example

-   We do regular addition but then apply (modn) on the result to get back a
    number in the range {0,…,n−1}
-   For a prime p, we can use the modp operation to also define a multiplication
    operation over the numbers {1,…,p−1} in a way that the multiplication result
    is also always in the set {1,…,p−1} – by performing regular multiplication
    of integers, and then taking the result modp.
-   Let us assume this set of elements together with this operation is referred
    to as the group $\mathbb{Z}_p^*$

## Homormophic Hiding Example(continued)

$\mathbb{Z}_p^*$ has the following properties :

-   It is a cyclic group; which means that $\exists g \in \mathbb{Z}_p^*$ called
    a generator such that all elements of $\mathbb{Z}_p^*$ can be written as
    $g^a$ for some $a \in \{0,..,p−2\}$, where we define $g^0=1$.
-   The discrete logarithm problem is believed to be hard in $\mathbb{Z}_p^*$ .
    This means that, when p is large, given an element h in $\mathbb{Z}_p^*$ it
    is difficult to find the integer a in 0,..,p−2 such that $g^a=h(mod p)$.
-   As "exponents add up when elements are multiplied", we have for a,b in
    0,..,p−2 $g^a⋅g^b=g^{a+b(mod p−1)}$.

We have now constructed an HH that ”supports addition” – meaning that E(x+y) is
computable from E(x) and E(y)

## Blind Evaluation of Polynomial

<!-- \tiny \[ \begin{bmatrix} x*{11} & x*{12} & x*{13} & \dots & x*{1n} \\ x*{21} & -->
<!-- x*{22} & x*{23} & \dots & x*{2n} \\ \hdotsfor{5} \\ x*{d1} & x*{d2} & x*{d3} & -->
<!-- \dots & x*{dn} \end{bmatrix} = \begin{bmatrix} x*{11} & x*{12} & x*{13} & \dots -->
<!-- & x*{1n} \\ x*{21} & x*{22} & x*{23} & \dots & x*{2n} \\ \vdots & \vdots & -->
<!-- \vdots & \ddots & \vdots \\ x*{d1} & x*{d2} & x*{d3} & \dots & x*{dn} -->
<!-- \end{bmatrix} \] \normalsize -->

-   A polynomial P of degree d over $\mathbb{F}_p$ is an expression of the form
    $P(s) = a_0 + a_1 . s + a_2 . s^2 + ... + a_d . s^d$ for some
    $a_0,..,a_d \in \mathbb{F}_p$

Suppose Alice has a polynomial P of degree d, and Bob has a point
$s \in \mathbb{F}_p$ that he chose randomly. Bob wishes to learn E(P(s)), i.e.,
the HH of the evaluation of P at s.

-   Using HH, we can perform blind evaluation as follows.
    -   Bob sends to Alice the hidings E(1),E(s),…,E(sd).
    -   Alice computes E(P(s)) from the elements sent in the first step, and
        sends E(P(s)) to Bob. (Alice can do this since E supports linear
        combinations, and P(s) is a linear combination of 1,s,…,$s^d$.)

<!-- ## Knowledge of Coefficient Assumption(KCA) -->

<!-- The KC(Knowledge of Coefficient) Test proceeds as follows. -->

<!-- -   Bob chooses random $α \in \mathbb{F}_p^*$ and $a \in G$. He computes -->
<!-- $b=α⋅a$. -->
<!-- -   He sends to Alice the “challenge” pair (a,b). Note that (a,b) is an -->
<!-- $α-pair$. -->
<!-- -   Alice must now respond with a different pair (a′,b′) that is also an -->
<!-- $α-pair$. -->
<!-- -   Bob accepts Alice’s response only if (a′,b′) is indeed an α-pair. (As he -->
<!-- knows $α$ he can check if $b′=α⋅a′$.) -->

<!-- Alice simply chooses some $γ \in \mathbb{F}_p^*$, and responds with -->
<!-- $(a′,b′)=(γ⋅a,γ⋅b)$. -->

<!-- ## Extended KCA -->

## QAP (Quadratic Arithmetic Program)

-   Gennaro, Gentry, Parno and Raykova(GGPR) defined an extremely useful
    translation of computations into polynomials called a Quadratic Arithmetic
    Program (QAP).
-   QAPs are sets of polynomials.
-   QAPs are building blocks to encode circuits into polynomials t and
    assignments into polynomials p.

## How to compute QAP?

-   Let I be circuit indices({1,..,m}). Then,

$$
QAP := \{t, \{v_k\}_{k∈I} , \{w_k\}_{k∈I} , \{y_k\}_{k∈I} \}
$$

-   Choose random elements $\{m_1 , · · · m_k \}$ from base field for every
    multiplication vertex in the circuit.
-   Target polynomial t(x) is computed as $(x- m_1)\otimes ... \otimes(x-m_k)$
-   Polynomial from $\{v_k \}_{k∈I}$ is 1 at $m_j$ , if edge k is left input to
    multiplication gate $\otimes m_j$ and zero at $m_j$ , otherwise.
-   Polynomial from $\{w_k\}_{k∈I}$ is 1 at $m_j$ , if edge k is right input to
    multiplication gate $\otimes m_j$ and zero at $m_j$ , otherwise.

## How to compute QAP?(continued)

-   Polynomial from $\{y_k\}_{k∈I}$ is 1 at $m_j$ , if edge k is output of
    multiplication gate $\otimes m_j$ and zero at $m_j$ , otherwise.
-   Circuit assignment $\{c_k\}_{k∈I}$ defines the polynomial, $\newline$ p :=
    $(\sum_{k∈I}{c_kv_k}) . (\sum_{k∈I}{c_kw_k}) -
    (\sum_{k∈I}{c_ky_k})$

## QAP Example

$QAP_{\mathbb{F}_{11}}(C_f) = \{ x^2 + 10x + 2, V, W, Y \} \newline where$

$V = \{ 5x+9, 0,0,6x+3, 0\}$

$W = \{0, 5x+9,6x+3,0,0\}$

$Y = \{0,0,0,5x+9,6x+3\}$

-   $\{c_k \}_{k∈I}$ is valid assignment $\iff$ p is divisible by t.

Valid example I = {2, 3, 4, 6, 2}: $\tiny$

-   (2(5x + 9) + 6(6x + 3)) · (3(5x + 9) + 4(6x + 3)) − (6(5x + 9) + 2(6x + 3))
-   (2·5x +2·9+6·6x +6·3)·(3·5x +3·9+4·6x +4·3)−(6·5x +6·9+2·6x +2·3) =
-   (10x + 7 + 3x + 7) · (4x + 5 + 2x + 1) − (8x + 10 + 1x + 6) =
-   (2x + 3) · (6x + 6) − (9x − 5) =
-   $x^2 + x + 7x + 7 + 2x + 6$
-   $\Rightarrow$ p(x) = $x^2 + 10x + 2$ – Equal to t hence divisible

$\normalsize$

## Assumptions Moving Forward {#Imid}

-   Let size of QAP be m and number of Input/Output variables of function F be
    N. m>=N as m also includes intermediate computation outputs. Degree of
    QAP(d) = degree(t(x)).
-   Let $I_{mid}$ = $\{N+1,..,m\}$ be the non IO related indices.

## Pinocchio Protocol

1.  $(EK_F ,VK_F) \leftarrow KeyGen(F, 1^λ ) \newline$ $\Rightarrow$ F be the
    function with N input/output values from $\mathbb{F}$, $\lambda$ is the
    security parameter, $EK_F$ is the Evaluation Key and $VK_F$ is the
    Verification Key
2.  $(y, \pi_y ) \leftarrow Compute(EK_F , u) \newline$ $\Rightarrow$ u is the
    input, y $\leftarrow$ F(u) and the $\pi_y$ is proof of y's correctness
3.  $\{0, 1\} \leftarrow Verify(VK_F , u, y, \pi_y ) \newline$ $\Rightarrow$ The
    deterministic verification algorithm outputs 1 if F(u) = y, and 0 otherwise.

## Requirements of the protocol

-   A finite cyclic group (G, ·)
-   A generator g of that group
-   A bilinear map B(·, ·) : $G × G → G_T$ , such that:
    -   Order: $G_T$ and G have the same order
    -   Bilinearity: $e(g^j,h^k) = e(g,h)^{j.k}$ for all j,k
        $\in \mathbb{Z}, g,h \in G$

This is usually there in cryptographically strong, pairing friendly elliptic
curve.

## KeyGen {#KeygenP1}

-   Choose random elements
    $r_v , r_w , s, \alpha_v , \alpha_w , \alpha_y , \beta, \gamma ∈ \mathbb{F}$
-   Set $r_y = r_v · r_w , g_v = g_{r_v} , g_w = g{r_w} and g_y = g{r_y} .$

Evaluation Key ($EK_F$)

![](./pics/EK.png)

-   It is the set of group elements, used to encrypt the non I/O(internal
    computations) related part of the polynomial p. This is clear from the usage
    of $I_{mid}$ which signifies the non IO related indices.[$[^1]$](#Imid)
-   Size depends linear on the number of internal (non I/O) edges in the
    circuit.

## KeyGen (continued) {#KeygenP2}

Verification Key ($VK_F$)

![](./pics/VK.png)

-   It is the set of group elements, used to encrypt the I/O related part of the
    polynomial p.
-   Size depends linear on the number of I/O edges in the circuit.
-   Delete all the randomly generated values.

## Compute {#ComputeP1}

-   Computation $\newline \Rightarrow$Given input set $I_{in}$ , execute circuit
    $C_f$ to compute intermediate values $I_{mid}$ and result $I_{out}$ .
-   Proof Generation

    -   Use valid assignment I and QAP to compute polynomial p.
    -   Derive quotient polynomial h = p/t.
    -   Use $EK_F$ to generate $\pi_y$

        ![](./pics/pi.png)

where
$v_m(x) = \sum_{k\in I_{mid}}{c_kv_k(x)},
w_m(x) = \sum_{k\in I_{mid}}{c_kw_k(x)},
y_m(x) = \sum_{k\in I_{mid}}{c_ky_k(x)}$

## Compute (continued) {#ComputeP2}

How does the proof get generated from $EK_F$?

-   All $v_k’s, w_k’s$ and $y_k’s$ are part of the QAP
-   We don't know any of the random values used during the [Keygen](#KeygenP1)
    phase.
-   We use $EK_F$ and exponential laws to generate the proof

    -   $g^x.g^y = g^{x+y}$
    -   $(g^x)^y = g^{x.y}$

-   All $c_k$ are known from execution
-   All $g^{r_v.v_k(s)} , g^{r_v.\alpha_v.v_k(s)}$ are provided in the $EK_F$

![](./pics/pi_p2.png)

## Verification {#VerifyP1}

-   Given input set $I_{in}$ , output set $I_{out}$ and proof $\pi$
-   Verify computer(worker) knows p such that p is divisible by t(target
    polynomial).
-   The verification of an alleged proof with elements $\pi$ =
    {$g^{V_{mid}} , g^{W_{mid}} , g^{Y_{mid}} , g^H , g^{V'_{mid}} ,g^{W'_{mid}} , g^{Y'_{mid}}
    , g^Z$}
    uses the public verification key $VK_F$ and the pairing function e for the
    following checks.

## Verification {#VerifyP2}

<!-- Divisibility check for the QAP: -->
<!-- -   Using elements from $VK_F$ , compute $g_v^{v_{I/O}(s)}$ = -->
<!-- $\prod_{k \in [N]}{(g_v^{v_k(s)})^{c_k}}$ -->
<!-- - Now check: -->

\centering ![](./pics/verify.png){width=50%}

<!-- ## Security Intuition of the proof(NOT sure?) -->

<!-- -   It seems hard for an adversary who does not know $\alpha$ to construct any -->
<!-- pair of group elements $h, h^{\alpha}$ except in the obvious way: by taking -->
<!-- pairs $(g_1 , g^α_1 ), (g_2 , g^α_2 )$ that he is given, and applying the -->
<!-- same linear combination (in the exponent) to the left and right elements of -->
<!-- the pairs. -->
<!-- -   This hardness is formalized in the d-PKE assumption, a sort of -->
<!-- “knowledge-of-exponent” assumption, that says that the adversary must “know” -->
<!-- such a linear combination, in the sense that this linear combination can be -->
<!-- extracted from him. -->

## Zero Knowledge

-   Suppose the worker does not want to publish (some of) the inputs

Verifier side changes

-   Extend verifier key in setup phase with
    {$g^{r_v.α_v.t(s)} , g^{r_w.α_w.t(s)} , g^{r_y.α_y.t(s)} , g^{r_v.β.t(s)} , g^{r_w.β.t(s)} , g^{r_y.β.t(s)}$}

Worker Side Changes

-   Generate random elements $\delta_v$ , $\delta_w$ , $\delta_y$ , and change
    -   $v_{mid}(x) \Rightarrow v_{mid}(x) + \delta_vt(x)$
    -   $v(x) \Rightarrow v(x) + \delta_vt(x)$
    -   $w(x) \Rightarrow w(x) + \delta_wt(x)$
    -   $y(x) \Rightarrow y(x) + \delta_yt(x)$

$$
p := (\sum_{k∈I}{c_k.v_k} + \delta_v.t(x))·(\sum_{k∈I}{c_k.w_k} + \delta_w.t(x)) − (\sum_{k∈I}{c_k.y_k} + \delta_y.t(x))
$$

has the same divisibility property with respect to t.

## References

-   [Electric Coin Blog](https://electriccoin.co/blog/snark-explain6/)
-   [Vitalic Buterin Medium Blog on QAP](https://medium.com/@VitalikButerin/quadratic-arithmetic-programs-from-zero-to-hero-f6d558cea649)
-   [risencrypto zkSnarks blog](https://risencrypto.github.io/zkSnarks/)
-   [The Mathematics behind zkSnarks(LeastAuthority Youtube Video)](https://youtu.be/iRQw2RpQAVc)
