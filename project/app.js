const input = document.querySelector("#temperature-input");
const fromUnit = document.querySelector("#from-unit");
const toUnit = document.querySelector("#to-unit");
const resultValue = document.querySelector("#result-value");
const validationMessage = document.querySelector("#validation-message");
const swapButton = document.querySelector("#swap-button");

const absoluteZero = { C: -273.15, F: -459.67, K: 0 };
const symbols = { C: "°C", F: "°F", K: "K" };
const formatter = new Intl.NumberFormat(undefined, {
  minimumFractionDigits: 2,
  maximumFractionDigits: 2,
});

function toKelvin(value, unit) {
  if (unit === "C") return value + 273.15;
  if (unit === "F") return (value - 32) * 5 / 9 + 273.15;
  return value;
}

function fromKelvin(value, unit) {
  if (unit === "C") return value - 273.15;
  if (unit === "F") return (value - 273.15) * 9 / 5 + 32;
  return value;
}

function format(value, unit) {
  return `${formatter.format(value)} ${symbols[unit]}`;
}

function convert() {
  const value = Number(input.value);
  if (input.value.trim() === "" || !Number.isFinite(value)) {
    validationMessage.textContent = "Enter a temperature to convert.";
    resultValue.textContent = "—";
    return;
  }
  if (value < absoluteZero[fromUnit.value]) {
    validationMessage.textContent = `The lowest possible temperature is ${absoluteZero[fromUnit.value]} ${symbols[fromUnit.value]}.`;
    resultValue.textContent = "—";
    return;
  }

  validationMessage.textContent = "";
  const kelvin = toKelvin(value, fromUnit.value);
  const converted = fromKelvin(kelvin, toUnit.value);
  resultValue.innerHTML = `${formatter.format(converted)}<span>${symbols[toUnit.value]}</span>`;
  document.querySelector("#celsius-value").textContent = format(fromKelvin(kelvin, "C"), "C");
  document.querySelector("#fahrenheit-value").textContent = format(fromKelvin(kelvin, "F"), "F");
  document.querySelector("#kelvin-value").textContent = format(kelvin, "K");
}

swapButton.addEventListener("click", () => {
  const previousFrom = fromUnit.value;
  fromUnit.value = toUnit.value;
  toUnit.value = previousFrom;
  convert();
});

input.addEventListener("input", convert);
fromUnit.addEventListener("change", convert);
toUnit.addEventListener("change", convert);
convert();