using Microsoft.VisualStudio.TestTools.UnitTesting;
using Project3CPSC3200;
using System;
using System.Collections.Generic;
using System.Numerics;
using System.Runtime.InteropServices;

namespace Project3CPSC3200Test {
    [TestClass]
    public class dataFilterTest {
        [TestMethod]
        public void Test_dataFilter_ConstructorPrime() {
            // Arrange/Act
            dataFilter d = new dataFilter(5);
            int[] testArray = new int[1] { 5 };

            // Assert
            CollectionAssert.AreEqual(d.filter(), testArray);
        }

        [TestMethod]
        public void Test_dataFilter_ConstructorNonPrime() {
            // Arrange/Act
            dataFilter d = new dataFilter(8);
            int[] testArray = new int[1] { 2 };

            // Assert
            CollectionAssert.AreEqual(d.filter(), testArray);
        }

        [TestMethod]
        public void Test_dataFilter_DefaultConstructor() {
            // Arrange/Act
            dataFilter d = new dataFilter();
            int[] testArray = new int[1] { 2 };

            // Assert
            CollectionAssert.AreEqual(d.filter(), testArray);
        }

        [TestMethod]
        public void Test_dataFilter_GetDefaultMode() {
            // Arrange/Act
            dataFilter d = new dataFilter();

            // Assert
            Assert.IsFalse(d.getMode());
        }

        [TestMethod]
        public void Test_dataFilter_SetMode() {
            // Arrange
            dataFilter d = new dataFilter();
            
            // Act
            d.setMode(true);

            // Assert
            Assert.IsTrue(d.getMode());
        }

        [TestMethod]
        public void Test_dataFilter_SetPrimeWithPrime() {
            // Arrange
            dataFilter d = new dataFilter();
            int[] testArray = new int[1] { 11 };

            // Act
            d.setPrime(11);

            // Assert
            CollectionAssert.AreEqual(d.filter(), testArray);
        }

        [TestMethod]
        public void Test_dataFilter_SetPrimeWithoutPrime() {
            // Arrange
            dataFilter d = new dataFilter(17);
            int[] testArray = new int[1] { 17 };

            // Act
            d.setPrime(18);

            // Assert
            CollectionAssert.AreEqual(d.filter(), testArray);
        }

        [TestMethod]
        public void Test_dataFilter_FilterSmallMode() {
            // Arrange
            dataFilter d = new dataFilter(23);
            int[] testArray = new int[7] { 25, 14, 29, 40, 8, 59, 2 };
            int[] assertArray = new int[3] { 14, 8, 2 };

            // Act
            d.scramble(testArray); // Using scramble to set array, ignoring its output in this test
            int[] dFilter = d.filter();

            // Assert
            CollectionAssert.AreEqual(dFilter, assertArray);
        }

        [TestMethod]
        public void Test_dataFilter_FilterLargeMode() {
            // Arrange
            dataFilter d = new dataFilter(41);
            d.setMode(true);
            int[] testArray = new int[7] { 59, 24, 37, 15, 63, 104, 2 };
            int[] assertArray = new int[3] { 59, 63, 104 };

            // Act
            d.scramble(testArray);
            int[] dFilter = d.filter();

            // Assert
            CollectionAssert.AreEqual(dFilter, assertArray);
        }

        [TestMethod]
        public void Test_dataFilter_ScrambleEvenLengthSeq() {
            // Arrange
            dataFilter d = new dataFilter();
            int[] testArray = new int[6] { 29, 14, 34, 73, 5, 9 };
            int[] assertArray = new int[6] { 14, 29, 34, 73, 5, 9 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }

        [TestMethod]
        public void Test_dataFilter_ScrambleOddLengthSeq() {
            // Arrange
            dataFilter d = new dataFilter();
            int[] testArray = new int[5] { 29, 14, 34, 73, 5 };
            int[] assertArray = new int[5] { 14, 29, 34, 73, 5 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }

        [TestMethod]
        public void Test_dataFilter_ScrambleLargeMode() {
            // Arrange
            dataFilter d = new dataFilter();
            d.setMode(true);
            int[] testArray = new int[6] { 29, 14, 34, 73, 5, 9 };
            int[] assertArray = new int[6] { 29, 14, 73, 34, 9, 5 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }
    }
}
