using Microsoft.VisualStudio.TestTools.UnitTesting;
using Project3CPSC3200;
using System;

namespace Project3CPSC3200Test {
    [TestClass]
    public class dataCutTest {
        [TestMethod]
        public void Test_dataCut_FilterSmallMode() {
            // Arrange
            dataCut d = new dataCut(17);
            int[] testArray = new int[6] { 23, 28, 4, 20, 5, 58 };
            int[] assertArray = new int[1] { 5 };

            // Act
            d.scramble(testArray);
            int[] dFilter = d.filter();

            // Assert
            CollectionAssert.AreEqual(dFilter, assertArray);
        }

        [TestMethod]
        public void Test_dataCut_FilterLargeMode() {
            // Arrange
            dataCut d = new dataCut(19);
            d.setMode(true);
            int[] testArray = new int[6] { 23, 28, 4, 20, 5, 58 };
            int[] assertArray = new int[3] { 23, 28, 20 };

            // Act
            d.scramble(testArray);
            int[] dFilter = d.filter();

            // Assert
            CollectionAssert.AreEqual(dFilter, assertArray);
        }

        [TestMethod]
        public void Test_dataCut_ScrambleRemoveLastScrambled() {
            // Arrange
            dataCut d = new dataCut(23);
            int[] testArray1 = new int[4] { 24, 17, 4, 10 }; // 17, 24, 4, 10
            int[] testArray2 = new int[] { 29, 14, 4, 33, 7 };
            int[] assertArray = new int[] { 14, 29, 7, 33 };

            // Act
            d.scramble(testArray1);
            int[] dScramble = d.scramble(testArray2);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }
    }
}
