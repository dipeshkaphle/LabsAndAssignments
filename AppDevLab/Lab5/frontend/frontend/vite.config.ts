import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import {PORT} from './config';


// https://vitejs.dev/config/
export default defineConfig({
  plugins: [react()],
  server:{
    port: PORT
  }
})
