/** @type {import('tailwindcss').Config} */
export default {
  content: ['./src/**/*.{html,js,svelte,ts}'],
  theme: {
    extend: {},
  },
  plugins: [require("daisyui")],

  daisyui: {
    themes: [
      {
        nightmod: {
          ...require("daisyui/src/theming/themes")["night"],
          "secondary": "#4338ca",
        }
      }, 
      "night",
      "aqua"
    ],
  }
}

