/** @type {import('tailwindcss').Config} */
module.exports = {
  content: [
    "./src/**/*.{html,js}",
    "../../templates/**/*.xml",
    "../../../src/*.cpp",
    "../../../src/include/*.h",
  ],
  corePlugins: { preflight: false },
  darkMode: "class",
  theme: {
    extend: {
      fontFamily: {
        body: ["Nunito"],
      },
    },
  },
  plugins: [],
};
