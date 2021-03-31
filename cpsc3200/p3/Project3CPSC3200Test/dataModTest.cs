using Microsoft.VisualStudio.TestTools.UnitTesting;
using Project3CPSC3200;
using System.Collections.Generic;

namespace Project3CPSC3200Test {
    [TestClass]
    public class dataModTest {
        [TestMethod]
        public void Test_dataMod_FilterSmallMode() {
            // Arrange
            dataMod d = new dataMod(13);
            int[] testArray = new int[6] { 8, 24, 30, 31, 6, 11 };
            int[] assertArray = new int[4] { 7, 1, 5, 1 };

            // Act
            d.scramble(testArray); // NOTE: All prime numbers will be replaced with '2' before updating
            int[] dFilter = d.filter();

            // Assert
            CollectionAssert.AreEqual(dFilter, assertArray);
        }

        [TestMethod]
        public void Test_dataMod_FilterLargeMode() {
            // Arrange
            dataMod d = new dataMod(13);
            d.setMode(true);
            int[] testArray = new int[6] { 8, 24, 30, 31, 6, 11 };
            int[] assertArray = new int[2] { 25, 31 };

            // Act
            d.scramble(testArray); // NOTE: All prime numbers will be replaced with '2' before updating
            int[] dFilter = d.filter();

            // Assert
            CollectionAssert.AreEqual(dFilter, assertArray);
        }

        [TestMethod]
        public void Test_dataMod_ScrambleEvenLengthSeq() {
            // Arrange
            dataMod d = new dataMod();
            int[] testArray = new int[6] { 8, 24, 30, 31, 6, 11 }; 
            int[] assertArray = new int[6] { 8, 24, 2, 30, 2, 6 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }

        [TestMethod]
        public void Test_dataMod_ScrambleOddLengthSeq() {
            // Arrange
            dataMod d = new dataMod();
            int[] testArray = new int[7] { 8, 24, 30, 31, 6, 11, 66 }; 
            int[] assertArray = new int[7] { 8, 24, 2, 30, 2, 6, 66 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }

        [TestMethod]
        public void Test_dataMod_ScrambleLargeMode() {
            // Arrange
            dataMod d = new dataMod();
            d.setMode(true);
            int[] testArray = new int[6] { 8, 24, 30, 31, 6, 11 }; 
            int[] assertArray = new int[6] { 24, 8, 30, 2, 6, 2 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }
    }
}
