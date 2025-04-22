<h1>🚀 Welcome to the C++ BigNumber Operations</h1>

  <p>A <strong>BigInteger</strong> class to handle arithmetic with arbitrarily large integers in C++, including full support for negative values.</p>

  <section>
    <h2>✨ Features</h2>
    <ul>
      <li><strong>Arbitrary Precision:</strong> Handles integers beyond built-in type limits (<code>int</code>, <code>long</code>, <code>long long</code>).</li>
      <li><strong>Signed Arithmetic:</strong> Supports positive and negative numbers.</li>
      <li><strong>Supported Operations:</strong>
        <ul>
          <li>Addition (<code>operator+</code>, <code>operator+=</code>)</li>
          <li>Subtraction (<code>operator-</code>, <code>operator-=</code>)</li>
          <li>Multiplication (<code>operator*</code>, <code>operator*=</code>)</li>
          <li>Division (<code>operator/</code>, <code>operator/=</code>)</li>
        </ul>
      </li>
      <li><strong>Exception Safety:</strong> Division by zero throws <code>invalid_argument</code>.</li>
    </ul>
  </section>

  <section class="usage">
    <h2>📦 Getting Started</h2>
    <h3>📁 Clone the Repository</h3>
    <pre><code>https://github.com/brijesh2004/Big_Numbers_Operations_in_CPP.git
cd BigIntegerLibrary</code></pre>
  </section>


<h2>Example</h2>
  <section>
     <code>
        int main(){
           BigInteger a = BIGInt(123849584858474398434884);
           BigInteger b = BIGInt(98765432109876543210);
           cout << a + b<< "\n";
           cout << a - b<< "\n";
           BigInteger c = BIGInt(-7);
           BigInteger d = BIGInt(2);
           BigInteger e = BIGInt(1111111111111111111111111111111111111111);
           cout<< c*e*d <<"\";
           cout<< c-d-e <<"\";
           cout<< c*d << "\";
           cout<< e/d <<"\";
           return 0;
      }
     </code>
   

   </pre>
  </section>

  <footer>
    <p>📘 Built with ❤️ in C++</p>
  </footer>
