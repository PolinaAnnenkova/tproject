<template>
  <div>
    <header class="bg-blue-300 p-4 flex items-center justify-between">
      <div class="flex items-center">
        <img src="@/assets/logo.png" alt="Logo" class="w-12 h-12 mr-2"/>
        <h1 class="text-white text-xl">Корпоративный портал учета рабочего времени</h1>
      </div>
      <button class="text-white">Новый сотрудник</button>
    </header>
    <div class="flex bg-blue-100">
      <aside class="bg-blue-100 w-1/4 p-4 h-screen overflow-y-auto">
        <div class="flex items-center mb-4">
          <svg class="w-6 h-6 mr-2 text-blue-600" fill="currentColor" viewBox="0 0 24 24">
            <path d="M16 11c1.657 0 3-1.343 3-3S17.657 5 16 5s-3 1.343-3 3 1.343 3 3 3zm2 1h-4c-2.21 0-4 1.79-4 4v4h12v-4c0-2.21-1.79-4-4-4z"/>
            <path d="M6 11c1.657 0 3-1.343 3-3S7.657 5 6 5 3 6.343 3 8s1.343 3 3 3zm2 1H4c-2.21 0-4 1.79-4 4v4h8v-4c0-2.21-1.79-4-4-4z"/>
          </svg>
          <span>Список сотрудников</span>
        </div>
        <ul>
          <li v-for="(employee, index) in employees" :key="index" class="mb-2">
            <a href="#" class="block p-2 bg-white rounded shadow">
              {{ employee.name }}
            </a>
          </li>
        </ul>
      </aside>
      <main class="flex-1 p-4">
        <nav class="flex space-x-4 mb-4">
          <button @click="currentTab = 'tasks'" 
                  :class="{'bg-blue-300 text-white': currentTab === 'tasks', 'text-blue-500': currentTab !== 'tasks'}" 
                  class="px-4 py-2 rounded">
            Задачи
          </button>
          <button @click="currentTab = 'projects'" 
                  :class="{'bg-blue-300 text-white': currentTab === 'projects', 'text-blue-500': currentTab !== 'projects'}" 
                  class="px-4 py-2 rounded">
            Проекты
          </button>
          <button @click="currentTab = 'transactions'" 
                  :class="{'bg-blue-300 text-white': currentTab === 'transactions', 'text-blue-500': currentTab !== 'transactions'}" 
                  class="px-4 py-2 rounded">
            Проводки
          </button>
        </nav>
        <div v-if="currentTab === 'projects'">
          <h2 class="text-2xl mb-4">Список проектов</h2>
          <table class="min-w-full bg-white">
            <thead class="bg-blue-300">
              <tr>
                <th class="w-1/3 px-4 py-2">Название</th>
                <th class="w-1/6 px-4 py-2">Код</th>
                <th class="w-1/6 px-4 py-2">Активный</th>
                <th class="w-1/3 px-4 py-2 text-center">Действия</th>
              </tr>
            </thead>
            <tbody>
              <tr v-for="(project, index) in projects" :key="project.code" class="border-t">
                <td class="px-4 py-2">
                  <input v-if="editingIndex === index" v-model="project.name" class="w-full px-2 py-1 border rounded" />
                  <span v-else>{{ project.name }}</span>
                </td>
                <td class="px-4 py-2">
                  <input v-if="editingIndex === index" v-model="project.code" class="w-full px-2 py-1 border rounded" />
                  <span v-else>{{ project.code }}</span>
                </td>
                <td class="px-4 py-2 text-center">
                  <input v-if="editingIndex === index" type="checkbox" v-model="project.active" />
                  <span v-else>{{ project.active ? 'Да' : 'Нет' }}</span>
                </td>
                <td class="px-4 py-2 text-center">
                  <button v-if="editingIndex === index" @click="saveProject(index)" class="text-green-500 mr-2">💾</button>
                  <button v-else @click="editProject(index)" class="text-blue-500 mr-2">✏️</button>
                  <button @click="deleteProject(index)" class="text-red-500">🗑️</button>
                </td>
              </tr>
              <tr>
                <td class="px-4 py-2">
                  <input v-model="newProject.name" class="w-full px-2 py-1 border rounded" placeholder="Название"/>
                </td>
                <td class="px-4 py-2">
                  <input v-model="newProject.code" class="w-full px-2 py-1 border rounded" placeholder="Код"/>
                </td>
                <td class="px-4 py-2 text-center">
                  <input type="checkbox" v-model="newProject.active"/>
                </td>
                <td class="px-4 py-2 text-center">
                  <button @click="addProject" class="text-blue-500">➕</button>
                </td>
              </tr>
            </tbody>
          </table>
        </div>
      </main>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      currentTab: 'projects',
      employees: Array(20).fill({ name: 'Имя Фамилия' }),
      projects: [
        { name: 'Название1', code: 1, active: true },
        { name: 'Название2', code: 2, active: true },
        { name: 'Название3', code: 3, active: true },
        { name: 'Название4', code: 4, active: false },
        { name: 'Название5', code: 5, active: true },
      ],
      newProject: { name: '', code: '', active: false },
      editingIndex: null
    };
  },
  methods: {
    addProject() {
      if (this.newProject.name && this.newProject.code) {
        this.projects.push({ ...this.newProject });
        this.newProject = { name: '', code: '', active: false };
      }
    },
    editProject(index) {
      this.editingIndex = index;
    },
    deleteProject(index) {
      this.projects.splice(index, 1);
      if (this.editingIndex === index) {
        this.editingIndex = null;
      }
    },
    saveProject(index) {
      this.editingIndex = null;
    }
  }
};
</script>

<style scoped>
/* Add any additional styles here */
</style>
