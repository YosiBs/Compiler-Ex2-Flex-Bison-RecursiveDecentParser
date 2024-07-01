# Compiler-Ex2-Flex-Bison-RecursiveDecentParser
<p align="center">
<img src="https://github.com/YosiBs/Compiler-Ex1-Flex/assets/105666011/5deb5877-223a-49ac-aea0-55f45c7852d5" alt="ex2 image" width="400">
</p>

<h2>Overview</h2>
<p>This repository contains the solution for the second exercise of the Compiler course. The exercise involved creating two versions of a parser: one using Flex &amp; Bison and the other using Flex &amp; Recursive Descent Parser.</p>

<h2>Files</h2>
<ul>
    <li><code>olympics.lex</code>: The Flex file containing the lexical analyzer definitions.</li>
    <li><code>olympics.y</code>: The Bison file containing the parser definitions for the bottom-up approach.</li>
    <li><code>olympics.c</code>: The C file containing the parser definitions for the top-down approach.</li>
    <li><code>test_olympics.txt</code>: A sample input file with data on Olympic sports and the years they were part of the games.</li>
    <li><code>Makefile</code>: A Makefile to compile the Flex and Bison code and run the parsers on the sample input.</li>
</ul>

<h2>Usage</h2>
<p>To compile and run the lexical analyzer and parsers, follow these steps:</p>

<h3>Bottom-Up Parser (Flex &amp; Bison)</h3>
<ol>
    <li>
      <strong>Generate the C source files using Flex and Bison</strong>:
    <pre><code>flex olympics.lex
bison -d olympics.y</code></pre>
    </li>
    <li>
    <strong>Compile the generated C source files</strong>:
    <pre><code>gcc -o olympics_bison lex.yy.c olympics.tab.c</code></pre>
    </li>
    <li>
    <strong>Run the parser with the sample input</strong>:
    <pre><code>./olympics_bison test_olympics.txt</code></pre>
    </li>
</ol>

<h3>Top-Down Parser (Flex &amp; Recursive Descent)</h3>
<ol>
    <li>
      <strong>Generate the C source file using Flex</strong>:
    <pre><code>flex olympics.lex</code></pre>
    </li>
    <li>
      <strong>Compile the generated C source file along with the parser file</strong>:
    <pre><code>gcc -o olympics_recursive lex.yy.c olympics.c</code></pre>
    </li>
    <li>
      <strong>Run the parser with the sample input</strong>:
    <pre><code>./olympics_recursive test_olympics.txt</code></pre>
    </li>
</ol>

<p>Another Option is to Open the terminal in a desired folder and run this commands:</p>
<ol>
  <li>
    <pre><code>make</code></pre>
  </li>
  <li>
    <pre><code>make run</code></pre>
  </li>
</ol>


<h2>Expected Output</h2>
<p>The parsers will output the names of sports that appeared in at least 7 Olympic games and the average number of games per sport. For example:</p>
<pre><code>sports which appeared in at least 7 olympic games:
Archery
Athletics
Basketball

average number of games per sport:  15.60</code></pre>

<h2>Authors</h2>
<ul>
    <li><a href="https://github.com/YosiBs">Yosi Ben Shushan</a></li>
</ul>

<h2>Additional Information</h2>
<p>The input format and token types are detailed in the exercise description. Refer to the <code>olympics.lex</code>, <code>olympics.y</code>, and <code>olympics.c</code> files for the specific regular expressions and grammar rules used to match each token type.</p>

<h2>References</h2>
<ul>
    <li><a href="https://westes.github.io/flex/manual/">Flex Manual</a></li>
    <li><a href="https://www.gnu.org/software/bison/manual/">Bison Manual</a></li>
</ul>

<h2>Notes</h2>
<p>Ensure Flex, Bison, and GCC are installed on your system to compile and run the parsers.</p>

<p><em>This project was completed as part of the Compiler course in June 2024.</em></p>
