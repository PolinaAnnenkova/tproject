<template>
  <div>
    <div class="flex bg-blue-100">
      <main class="flex-1 p-4">
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
                  <input v-if="editingIndex === index" v-model="editProjectData.name" class="w-full px-2 py-1 border rounded" />
                  <span v-else>{{ project.name }}</span>
                </td>
                <td class="px-4 py-2">
                  <input v-if="editingIndex === index" v-model="editProjectData.code" class="w-full px-2 py-1 border rounded" />
                  <span v-else>{{ project.code }}</span>
                </td>
                <td class="px-4 py-2">
                  <input type="checkbox" v-if="editingIndex === index" v-model="editProjectData.active" />
                  <span v-else>{{ project.active ? 'Да' : 'Нет' }}</span>
                </td>
                <td class="px-4 py-2 text-center">
                  <button @click="editProject(index)" class="text-blue-500 mr-2" v-if="editingIndex !== index">✏️</button>
                  <button @click="saveProject(index)" class="text-green-500 mr-2" v-if="editingIndex === index">💾</button>
                  <button @click="cancelEdit()" class="text-red-500 mr-2" v-if="editingIndex === index">✖️</button>
                  <button @click="deleteProject(index)" class="text-red-500">🗑️</button>
                </td>
              </tr>
              <tr>
                <td class="px-4 py-2">
                  <input v-model="newProject.name" class="w-full px-2 py-1 border rounded" placeholder="Название" />
                </td>
                <td class="px-4 py-2">
                  <input v-model="newProject.code" class="w-full px-2 py-1 border rounded" placeholder="Код" />
                </td>
                <td class="px-4 py-2 text-center">
                  <input type="checkbox" v-model="newProject.active" />
                </td>
                <td class="px-4 py-2 text-center">
                  <button @click="addProject" class="text-blue-500">➕</button>
                </td>
              </tr>
            </tbody>
          </table>
          <div v-if="errorMessage" class="mt-4 text-red-500">
            {{ errorMessage }}
          </div>
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
      projects: [
        { name: 'Название1', code: 1, active: true },
        { name: 'Название2', code: 2, active: true },
        { name: 'Название3', code: 3, active: true },
        { name: 'Название4', code: 4, active: false },
        { name: 'Название5', code: 5, active: true },
      ],
      newProject: { name: '', code: '', active: false },
      editingIndex: null,
      editProjectData: { name: '', code: '', active: false },
      errorMessage: ''
    };
  },
  methods: {
    validateProjectData(project) {
      if (!project.name || !project.code) {
        this.errorMessage = 'Название и код проекта не могут быть пустыми.';
        return false;
      }
      if (isNaN(project.code)) {
        this.errorMessage = 'Код проекта должен быть числом.';
        return false;
      }
      if (typeof project.name !== 'string') {
        this.errorMessage = 'Название проекта должно быть текстом.';
        return false;
      }
      this.errorMessage = '';
      return true;
    },
    addProject() {
      if (this.validateProjectData(this.newProject)) {
        this.projects.push({ ...this.newProject });
        this.newProject = { name: '', code: '', active: false };
      }
    },
    editProject(index) {
      this.editingIndex = index;
      this.editProjectData = { ...this.projects[index] };
    },
    saveProject(index) {
      if (this.validateProjectData(this.editProjectData)) {
        this.projects.splice(index, 1, this.editProjectData);
        this.cancelEdit();
      }
    },
    deleteProject(index) {
      this.projects.splice(index, 1);
    },
    cancelEdit() {
      this.editingIndex = null;
      this.editProjectData = { name: '', code: '', active: false };
      this.errorMessage = '';
    }
  }
};
</script>

<style scoped>
/* Add any additional styles here */
</style>
