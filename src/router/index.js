import { createRouter, createWebHistory } from 'vue-router';
import ProjectsList from '../components/ProjectsList.vue';
import Provodki from '../components/Provodki.vue';

const routes = [
  { path: '/projects', component: ProjectsList },
  { path: '/transactions', component: Provodki },
  { path: '/', redirect: '/projects' } // Default route
];

const router = createRouter({
  history: createWebHistory(),
  routes
});

export default router;
