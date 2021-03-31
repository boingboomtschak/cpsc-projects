using Microsoft.VisualStudio.TestPlatform.ObjectModel.Client;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Project5CPSC3200;
using System;

namespace Project5CPSC3200Test {
    [TestClass]
    public class dataCutQuirkyBeaconTest {
        [TestMethod]
        public void Test_dataCutQuirkyBeacon_FilterSmallMode() {
            // Arrange
            dataCutQuirkyBeacon d = new dataCutQuirkyBeacon(17);
            int[] testArray = new int[6] { 23, 28, 4, 20, 5, 58 };
            int[] assertArray = new int[1] { 5 };

            // Act
            d.scramble(testArray);
            int[] dFilter = d.filter();

            // Assert
            CollectionAssert.AreEqual(dFilter, assertArray);
        }

        [TestMethod]
        public void Test_dataCutQuirkyBeacon_FilterLargeMode() {
            // Arrange
            dataCutQuirkyBeacon d = new dataCutQuirkyBeacon(19);
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
        public void Test_dataCutQuirkyBeacon_ScrambleRemoveLastScrambled() {
            // Arrange
            dataCutQuirkyBeacon d = new dataCutQuirkyBeacon(23);
            int[] testArray1 = new int[4] { 24, 17, 4, 10 }; // 17, 24, 4, 10
            int[] testArray2 = new int[] { 29, 14, 4, 33, 7 };
            int[] assertArray = new int[] { 14, 29, 7, 33 };

            // Act
            d.scramble(testArray1);
            int[] dScramble = d.scramble(testArray2);

            // Assert
            CollectionAssert.AreEqual(dScramble, assertArray);
        }
        [TestMethod]
        public void Test_dataCutQuirkyBeacon_SignalSetSeq() {
            // Arrange
            dataCutQuirkyBeacon bc = new dataCutQuirkyBeacon();
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
        public void Test_dataCutQuirkyBeacon_ChargeFns() {
            // Arrange
            dataCutQuirkyBeacon bc = new dataCutQuirkyBeacon();
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
        public void Test_dataCutQuirkyBeacon_StateFns() {
            // Arrange
            dataCutQuirkyBeacon bc = new dataCutQuirkyBeacon();
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
