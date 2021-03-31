using Microsoft.VisualStudio.TestPlatform.ObjectModel.Client;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Project5CPSC3200;
using System;

namespace Project5CPSC3200Test {
    [TestClass]
    public class dataModQuirkyBeaconTest {
        [TestMethod]
        public void Test_dataModQuirkyBeacon_FilterSmallMode() {
            // Arrange
            dataModQuirkyBeacon d = new dataModQuirkyBeacon(13);
            int[] testArray = new int[6] { 8, 24, 30, 31, 6, 11 };
            int[] assertArray = new int[4] { 7, 1, 5, 1 };

            // Act
            d.scramble(testArray); // NOTE: All prime numbers will be replaced with '2' before updating
            int[] dFilter = d.filter();

            // Assert
            CollectionAssert.AreEqual(dFilter, assertArray);
        }

        [TestMethod]
        public void Test_dataModQuirkyBeacon_FilterLargeMode() {
            // Arrange
            dataModQuirkyBeacon d = new dataModQuirkyBeacon(13);
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
        public void Test_dataModQuirkyBeacon_ScrambleEvenLengthSeq() {
            // Arrange
            dataModQuirkyBeacon d = new dataModQuirkyBeacon();
            int[] testArray = new int[6] { 8, 24, 30, 31, 6, 11 };
            int[] assertArray = new int[6] { 8, 24, 2, 30, 2, 6 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }

        [TestMethod]
        public void Test_dataModQuirkyBeacon_ScrambleOddLengthSeq() {
            // Arrange
            dataModQuirkyBeacon d = new dataModQuirkyBeacon();
            int[] testArray = new int[7] { 8, 24, 30, 31, 6, 11, 66 };
            int[] assertArray = new int[7] { 8, 24, 2, 30, 2, 6, 66 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }

        [TestMethod]
        public void Test_dataModQuirkyBeacon_ScrambleLargeMode() {
            // Arrange
            dataModQuirkyBeacon d = new dataModQuirkyBeacon();
            d.setMode(true);
            int[] testArray = new int[6] { 8, 24, 30, 31, 6, 11 };
            int[] assertArray = new int[6] { 24, 8, 30, 2, 6, 2 };

            // Act
            int[] dScramble = d.scramble(testArray);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }
        [TestMethod]
        public void Test_dataModQuirkyBeacon_SignalSetSeq() {
            // Arrange
            dataModQuirkyBeacon bc = new dataModQuirkyBeacon();
            int[] testArray = new int[] { 1, 2, 3, 4, 5 };
            int[] signalArray = new int[5];

            // Act
            bc.setSeq(testArray);
            for (int i = 0; i < signalArray.Length; i++) {
                signalArray[i] = bc.signal();
            }

            // Assert
            CollectionAssert.DoesNotContain(signalArray, 0);
        }

        [TestMethod]
        public void Test_dataModQuirkyBeacon_ChargeFns() {
            // Arrange
            dataModQuirkyBeacon bc = new dataModQuirkyBeacon();
            int[] testArray = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            int[] signalArray = new int[11];
            int[] signalArrayValid = new int[10];

            // Act
            bc.setSeq(testArray);
            for (int i = 0; i < signalArray.Length; i++) {
                signalArray[i] = bc.signal();
            }
            for (int i = 0; i < signalArrayValid.Length; i++) {
                signalArrayValid[i] = signalArray[i];
            }
            bc.recharge(5);

            // Assert
            Assert.AreEqual(bc.getCharge(), 5);
            Assert.AreEqual(signalArray[10], 0);
            CollectionAssert.DoesNotContain(signalArrayValid, 0);
        }

        [TestMethod]
        public void Test_dataModQuirkyBeacon_StateFns() {
            // Arrange
            dataModQuirkyBeacon bc = new dataModQuirkyBeacon();
            int[] testArray = new int[] { 1, 2, 3, 4 };
            int[] signalArrayValid = new int[4];
            int[] signalArrayInvalid = new int[4];

            // Act
            bc.setSeq(testArray);
            for (int i = 0; i < signalArrayValid.Length; i++) {
                signalArrayValid[i] = bc.signal();
            }
            for (int i = 0; i < 4; i++) {
                bc.turnOn();
            }
            for (int i = 0; i < signalArrayInvalid.Length; i++) {
                signalArrayInvalid[i] = bc.signal();
            }

            // Assert
            CollectionAssert.DoesNotContain(signalArrayValid, 0);
        }
    }
}
