/** @type {import('tailwindcss').Config} */
module.exports = {
  content: [
    "./src/**/*.html",
    "../templates/**/*.xml",
    "../../src/**/*.cpp",
    "../../src/**/*.h",
    "./node_modules/tw-elements/dist/js/**/*.js",
  ],
  plugins: [require("tw-elements/dist/plugin.cjs")],
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
