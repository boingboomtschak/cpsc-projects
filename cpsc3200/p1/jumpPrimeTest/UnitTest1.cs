using Microsoft.VisualStudio.TestTools.UnitTesting;
using Project1CPSC3200;

namespace jumpPrimeTest {
    [TestClass]
    public class UnitTest1 {
        [TestMethod]
        public void Test_ValidConstructor_jumpPrime() {
            jumpPrime j = new jumpPrime(1424);
            Assert.AreEqual(j.up(), 1427);
            Assert.AreEqual(j.down(), 1423);
        }

        [TestMethod]
        public void Test_InvalidConstructor_jumpPrime() {
            jumpPrime j = new jumpPrime(5);
            Assert.AreEqual(j.up(), 0);
            Assert.AreEqual(j.down(), 0);
        }



        [TestMethod]
        public void Test() {

        }
    }
}
