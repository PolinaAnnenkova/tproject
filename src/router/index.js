import { createRouter, createWebHistory } from 'vue-router'

import MainPageVue from '../components/MainPage.vue'
const routes = [
  {
    path: '/',
        name: 'main',
        component: MainPageVue
  },
  {
    path: '/tasks',
      name: 'tasks',
    // route level code-splitting
    // this generates a separate chunk (about.[hash].js) for this route
    // which is lazy-loaded when the route is visited.
    component: () => import(/* webpackChunkName: "about" */ '../components/TasksList.vue')
    },
    {
        path: '/projects',
        name: 'projects',
        // route level code-splitting
        // this generates a separate chunk (about.[hash].js) for this route
        // which is lazy-loaded when the route is visited.
        component: () => import(/* webpackChunkName: "about" */ '../components/ProjectsList.vue')
    },
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
})

export default router